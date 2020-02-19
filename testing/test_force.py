import mdsys_struct as md
import ctypes as ct


psys=md.mdsys()

psys.natoms = 3;             
psys.nfi=0;
psys.nsteps = 10000;      
psys.mass = 39.948;      
psys.epsilon = 0.2379;      
psys.sigma = 3.405;          
psys.rcut = 8.5;              
psys.box = 17.1580;          
psys.dt=5.0;                   


psys.rx = (ct.c_double * psys.natoms)()
psys.ry = (ct.c_double * psys.natoms)()
psys.rz = (ct.c_double * psys.natoms)()
psys.fx = (ct.c_double * psys.natoms)()
psys.fy = (ct.c_double * psys.natoms)()
psys.fz = (ct.c_double * psys.natoms)()

eps = 1e-5;
    
#Set position of atoms - r[0] r[1] fixed on ax,ay and sigma distance between az | r[2] outside
psys.rx[0]=1;
psys.ry[0]=1;	
psys.rz[0]=1;
psys.rx[1]=1;
psys.ry[1]=1;
psys.rz[1]=4.405;
psys.rx[2]=29.19613239880890;
psys.ry[2]=-30.97120493339350;
psys.rz[2]=-17.97120493339350;

psys.force();

print("\n\nr[0] r[1] fixed on axis x,y and sigma distance on axis z | r[2] out of the box\n");
for i in range(psys.natoms):
		print("Fx  %20.8f %20.8f %20.8f\n" % (psys.fx[i], psys.fy[i], psys.fz[i]));

test_epot= -0.01903649


if abs(psys.epot - test_epot) <= eps: 
  print("Test-1 on potential energy successful!\n")
else:
  print("Test-1 on potential energy failed!\n")
  exit(1)	

#Set position of atoms - r[0] r[1] fixed on ax,ay and sigma distance between az | r[2] inside
psys.rx[0]=1;
psys.ry[0]=1;	
psys.rz[0]=1;
psys.rx[1]=1;
psys.ry[1]=1;
psys.rz[1]=4.405;
psys.rx[2]=2.19;
psys.ry[2]=-3.90;
psys.rz[2]=-4.9350;

psys.force();
	
print("r[0] r[1] fixed on axis x,y and sigma distance on axis z | r[2] inside the box\n");

test_epot= -0.006601053960292

if abs(psys.epot - test_epot) <= eps: 
  print("Test-2 on potential energy successful!\n")
else:
  print("Test-2 on potential energy failed!\n")
  exit(1)	
