import ctypes as ct
import sys

so_force = "../lib/compute_forces.so"
c_force = ct.CDLL(so_force)
so_ekin ="../lib/kinetic.so"
c_ekin=ct.CDLL(so_ekin)
so_velverlet="../lib/velocity.so"
c_velverlet=ct.CDLL(so_velverlet)
#so_mdloop="../lib/md_loop.so"
#c_mdloop=ct.CDLL(so_mdloop)


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
                 ("dt",ct.c_double), ("mass",ct.c_double), ("epsilon", ct.c_double), ("sigma", ct.c_double), ("box", ct.c_double), ("rcut", ct.c_double), ("ekin", ct.c_double), ("epot", ct.c_double), ("temp", ct.c_double), ("rx", ct.POINTER(ct.c_double)), ("ry", ct.POINTER(ct.c_double)), ("rz", ct.POINTER(ct.c_double)), ("vx", ct.POINTER(ct.c_double)), ("vy", ct.POINTER(ct.c_double)), ("vz", ct.POINTER(ct.c_double)), ("fx", ct.POINTER(ct.c_double)),("fy", ct.POINTER(ct.c_double)), ("fz", ct.POINTER(ct.c_double)) ]
   
  def __init__(self,rrank):
    self.nfi=0
    self.rank=rrank
    self.force_func = wrap_function(c_force, 'force', None, [ct.POINTER(mdsys)])
    self.ekin_func = wrap_function(c_ekin, 'ekin', None, [ct.POINTER(mdsys)])
    self.velverlet_func = wrap_function(c_ekin, 'velverlet', None, [ct.POINTER(mdsys)])
 #   self.md_loop_func = wrap_function(c_mdloop, 'md_loop', None, [ct.POINTER(mdsys)])
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
      self.trajf=open(self.ergfile,'w')

    
  def force(self):
    self.force_func(self)

  #trying to stick close to c code, but can't keep both function and field with the same name
  def ekin_f(self):
    self.ekin_func(self)
 
  def velverlet(self):
    self.velverlet_func(self)
   
  #def md_loop(self):
  #  self.md_loop_func(self) 
   
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
      
  def fill_pos_vel(self):
    self.alloc_ptrs()
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


  def finalize(self):
    self.ergf.close()
    self.trajf.close()
