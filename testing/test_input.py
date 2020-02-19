import mdsys_struct as md
import ctypes as ct


psys=md.mdsys()


psys.rank=0

psys.read_input()

if psys.natoms != 108:
  print(" The read input function has failed at atoms number\n")
  exit(1)
if abs(psys.mass- 39.948)> 1e-15: 
  print("The read input function has failed at mass\n")
  exit(1)
if abs(psys.epsilon - 0.2379) > 1e-15: 
  print("The read input function has failed at epsilon\n")
  exit(1)
if abs(psys.sigma - 3.405) > 1e-15:
  print("The read input function has failed at sigma \n")
if abs(psys.rcut - 8.5) > 1e-15:
  print("The read input function has failed\n")
  exit(1)
if abs(psys.box - 17.1580) > 1e-15: 
  print("The read input function has failed at box\n")
if abs(psys.nsteps!=10000): 
  print("The read input function has failed at steps number\n")
if abs(psys.dt-5.0) > 1e-15: 
  print("The read input function has failed at time step\n")
if psys.nprint != 100: 
  print("The read input function has failed at nprint\n")
  exit(1)
if psys.restfile != 'argon_108.rest':
  print("The read input function has failed at first filename\n")
  exit(1)
if psys.trajfile != 'argon_108.xyz':
  print("The read input function has failed at second filename\n")
  exit(1)
if psys.ergfile != 'argon_108.dat':
  print("The read input function has failed at 3rd filename\n")
  exit(1)

print("The read input function works correctly\n");  
