import ctypes as ct
import sys

so_ljmd = "../lib/ljmd.so"
c_ljmd = ct.CDLL(so_ljmd)

def wrap_function(lib, funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = lib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

#reads a line from an open file and strips comments
def get_a_line(ifile) :
  line = ifile.readline()
  line = line.partition('#')[0]
  line = line.rstrip()
  return line

class mdsys(ct.Structure):
  _fields_ = [ ("natoms", ct.c_int), ("nfi", ct.c_int), ("nsteps",ct.c_int), ("rank", ct.c_int), ("nps", ct.c_int),
                 ("dt",ct.c_double), ("mass",ct.c_double), ("epsilon", ct.c_double), ("sigma", ct.c_double), ("box", ct.c_double), ("rcut", ct.c_double), ("ekin", ct.c_double), ("epot", ct.c_double), ("temp", ct.c_double), ("rx", ct.POINTER(ct.c_double)), ("ry", ct.POINTER(ct.c_double)), ("rz", ct.POINTER(ct.c_double)), ("vx", ct.POINTER(ct.c_double)), ("vy", ct.POINTER(ct.c_double)), ("vz", ct.POINTER(ct.c_double)), ("fx", ct.POINTER(ct.c_double)),("fy", ct.POINTER(ct.c_double)), ("fz", ct.POINTER(ct.c_double)), ("cx", ct.POINTER(ct.c_double)),("cy", ct.POINTER(ct.c_double)), ("cz", ct.POINTER(ct.c_double)) ]
   
  def __init__(self):
    self.nfi=0
    self.force_func = wrap_function(c_ljmd, 'force', None, [ct.POINTER(mdsys)])
    self.ekin_func = wrap_function(c_ljmd, 'ekin', None, [ct.POINTER(mdsys)])
    self.vel1_func = wrap_function(c_ljmd, 'vel_step1', None, [ct.POINTER(mdsys)])
    self.vel2_func = wrap_function(c_ljmd, 'vel_step2', None, [ct.POINTER(mdsys)])
    self.initial_func = wrap_function(c_ljmd, 'initialize_mpi', None, [ct.POINTER(mdsys)])
    self.finalize = wrap_function(c_ljmd, 'finalize_mpi', None, None)
    self.broadcast_vals_func = wrap_function(c_ljmd, 'broadcast_values', None, [ct.POINTER(mdsys)])
    self.broadcast_arrs_func = wrap_function(c_ljmd, 'broadcast_arrays', None, [ct.POINTER(mdsys)])
    self.extra_alloc_func = wrap_function(c_ljmd, 'allocate_cs', None, [ct.POINTER(mdsys)])
    self.extra_free_func = wrap_function(c_ljmd, 'free_cs', None, [ct.POINTER(mdsys)])
 #   self.md_loop_func = wrap_function(c_mdloop, 'md_loop', None, [ct.POINTER(mdsys)])
    
  def force(self):
    self.force_func(self)

  #trying to stick close to c code, but can't keep both function and field with the same name
  def ekin_f(self):
    self.ekin_func(self)

  def vel1(self):
    self.vel1_func(self)
  
  def vel2(self):
    self.vel2_func(self)
    
  def finalize(self):
    self.finalize_func(self)
    
  def initial(self):
    self.initial_func(self)

  def broadcast_arrs(self):
    self.broadcast_arrs_func(self)
    
  def broadcast_vals(self):
    self.broadcast_vals_func(self)
    
  def extra_alloc(self):
    self.extra_alloc_func(self)
    
  def extra_free(self):
    self.extra_free_func(self)
   
  def alloc_ptrs(self):
    self.rx = (ct.c_double * self.natoms)()
    self.ry = (ct.c_double * self.natoms)()
    self.rz = (ct.c_double * self.natoms)()
    self.vx = (ct.c_double * self.natoms)()
    self.vy = (ct.c_double * self.natoms)()
    self.vz = (ct.c_double * self.natoms)()
    self.fx = (ct.c_double * self.natoms)()
    self.fy = (ct.c_double * self.natoms)()
    self.fz = (ct.c_double * self.natoms)()
      
  def read_input(self):
    if self.rank==0:
      with sys.stdin as input_file: 
        self.natoms=int(get_a_line(input_file));
        self.mass=float(get_a_line(input_file));
        self.epsilon=float(get_a_line(input_file));
        self.sigma=float(get_a_line(input_file));
        self.rcut=float(get_a_line(input_file));
        self.box=float(get_a_line(input_file));
        self.restfile=get_a_line(input_file)
        self.trajfile=get_a_line(input_file)
        self.ergfile=get_a_line(input_file)
        self.nsteps=int(get_a_line(input_file));
        self.dt=float(get_a_line(input_file));
        self.nprint=int(get_a_line(input_file));
      self.ergf=open(self.ergfile,'w')
      self.trajf=open(self.trajfile,'w')    
      
      
  def fill_pos_vel(self):
    with open(self.restfile,'r') as input_file:
      for i in range(self.natoms):
        line = input_file.readline()
        val_list = [float(j) for j in line.split()]
        self.rx[i]= val_list[0]
        self.ry[i]=val_list[1]
        self.rz[i]=val_list[2]
      for i in range(self.natoms):   
        line = input_file.readline()
        val_list = [float(j) for j in line.split()]
        self.vx[i]=val_list[0]
        self.vy[i]=val_list[1]
        self.vz[i]=val_list[2]
    
  def output(self):
    print("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n" % (self.nfi, self.temp, self.ekin, self.epot, self.ekin+self.epot));
    self.ergf.write("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n" % (self.nfi, self.temp, self.ekin, self.epot, self.ekin+self.epot));
    self.trajf.write("%d\n nfi=%d etot=%20.8f\n"% (self.natoms, self.nfi, self.ekin+self.epot));
    for i in range(self.natoms):
      self.trajf.write("Ar  %20.8f %20.8f %20.8f\n" % (self.rx[i], self.ry[i], self.rz[i])); 


  def close_files(self):
    self.ergf.close()
    self.trajf.close()
