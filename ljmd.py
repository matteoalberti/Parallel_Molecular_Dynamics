#import ctypes as ct
import sys
import mdsys_struct as md

#reads a line from an open file and strips comments
def get_a_line(ifile) :
  line = ifile.readline()
  line = line.partition('#')[0]
  line = line.rstrip()
  return line

#calling the system variable "sys" would be confusing as "sys" is a rather standart module, so we call it psys
psys=md.mdsys()

psys.nfi=0

with sys.stdin as input_file: 
    psys.natoms=int(get_a_line(input_file));
    psys.mass=float(get_a_line(input_file));
    psys.epsilon=float(get_a_line(input_file));
    psys.sigma=float(get_a_line(input_file));
    psys.rcut=float(get_a_line(input_file));
    psys.box=float(get_a_line(input_file));
    restfile=get_a_line(input_file)
    trajfile=get_a_line(input_file)
    ergfile=get_a_line(input_file)
    psys.nsteps=int(get_a_line(input_file));
    psys.dt=float(get_a_line(input_file));
    nprint=int(get_a_line(input_file));

  
psys.fill_pos_vel(restfile)    
psys.output(trajfile)

  
  
  
