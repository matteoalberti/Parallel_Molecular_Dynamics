import ctypes as ct

def wrap_function(lib, funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = lib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

class mdsys(ct.Structure):
    _fields_ = [ ("natoms", ct.c_int), ("nfi", ct.c_int), ("nsteps",ct.c_int),
                 ("dt",ct.c_double), ("mass",ct.c_double), ("epsilon", ct.c_double), ("sigma", ct.c_double), ("box", ct.c_double), ("rcut", ct.c_double), ("ekin", ct.c_double), ("epot", ct.c_double), ("temp", ct.c_double), ("rx", ct.POINTER(ct.c_double)), ("ry", ct.POINTER(ct.c_double)), ("rz", ct.POINTER(ct.c_double)), ("vx", ct.POINTER(ct.c_double)), ("vy", ct.POINTER(ct.c_double)), ("vz", ct.POINTER(ct.c_double)), ("fx", ct.POINTER(ct.c_double)),("fy", ct.POINTER(ct.c_double)), ("fz", ct.POINTER(ct.c_double)) ]
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
      
    #we decided not to deal with reading cvs by chunks (in case of big files) and resorted to c-style reading  
    def fill_pos_vel(self,ifile):
      self.alloc_ptrs()
      with open(ifile,'r') as input_file:
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
  
    
    def output(self,ofile):
      with open(ofile, 'w') as output_file:  
        for i in range(self.natoms):
          output_file.write("Ar  %20.8f %20.8f %20.8f\n" % (self.rx[i], self.ry[i], self.rz[i])); 
