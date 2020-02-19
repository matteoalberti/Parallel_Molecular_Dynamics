import mdsys_struct as md
import ctypes as ct


psys=md.mdsys()

psys.natoms = 2;             
psys.nfi=0;
psys.nsteps = 10000;      
psys.mass = 39.948;      
psys.epsilon = 0.2379;      
psys.sigma = 3.405;          
psys.rcut = 8.5;              
psys.box = 17.1580;          
psys.dt=5.0;                   


psys.vx = (ct.c_double * psys.natoms)()
psys.vy = (ct.c_double * psys.natoms)()
psys.vz = (ct.c_double * psys.natoms)()

eps = 1e-10;
    
#particle one    
psys.vx[0] = 0.0
psys.vy[0] = 0.0
psys.vz[0] = 0.0

#particle two 
psys.vx[1] = 0.0
psys.vy[1] = 0.0
psys.vz[1] = 0.0

#zero energy and forces 
psys.epot=0.0
psys.ekin=0.0

#Test value energy
test_ekin = 0.0

psys.ekin_f();

print("***Test-1 unit for Kinetic Energy***\n")
print("Initial particle velocity:\n")

print("v1=(%.8f, %.8f, %.8f),\n" % (psys.vx[0], psys.vy[0], psys.vz[0])) 
print("v2=(%.8f, %.8f, %.8f)\n" %  (psys.vx[1], psys.vy[1], psys.vz[1])) 

if (psys.ekin - test_ekin) < eps: 
    print("Test-1 on kinetic energy successful!\n")
else:
    print("Test-1 on kinetic energy failed!\n")
    exit(1)

#second test

#particle one
psys.vx[0] = 1.;
psys.vy[0] = 1.;
psys.vz[0] = 1.;

#particle two 
psys.vx[1] = 0.;
psys.vy[1] = 0.;
psys.vz[1] = 0.;

#zero energy and forces 
psys.epot=0.0;
psys.ekin=0.0;

#Test value energy
test_ekin = 143217.01721781;

psys.ekin_f();

print("\n***Test-2 unit for Kinetic Energy***\n");
print("Initial particle velocity:\n");

print("v1=(%.8f, %.8f, %.8f),\n" % (psys.vx[0], psys.vy[0], psys.vz[0])) 
print("v2=(%.8f, %.8f, %.8f)\n"% (psys.vx[1], psys.vy[1], psys.vz[1]))

if (psys.ekin - test_ekin) <= eps: 
  print("Test-2 on kinetic energy successful!\n")
else:
  print("Test-2 on kinetic energy failed!\n")
  exit(1)
  
#test 3

# particle one 
psys.vx[0] = 1e2;
psys.vy[0] = 0.;
psys.vz[0] = -1e2;

#particle two */
psys.vx[1] = -1e2
psys.vy[1] = 0.
psys.vz[1] = 1e2

#zero energy and forces 
psys.epot=0.0
psys.ekin=0.0

#Test value energy
test_ekin = 1909560229.57079720;

psys.ekin_f()

print("\n***Test-3 unit for Kinetic Energy***\n")
print("Initial particle velocity:\n")

print("v1=(%.8f, %.8f, %.8f),\n" % (psys.vx[0], psys.vy[0], psys.vz[0])) 
print("v2=(%.8f, %.8f, %.8f)\n"% (psys.vx[1], psys.vy[1], psys.vz[1]))

if (psys.ekin - test_ekin) <= eps: 
  print("Test-3 on kinetic energy successful!\n")
else:
  print("Test-3 on kinetic energy failed!\n")
  exit(1)

