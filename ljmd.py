import mdsys_struct as md

rank=0
#calling the system variable "sys" would be confusing as "sys" is a rather standart module, so we call it psys
psys=md.mdsys(rank)


#broadcast size here
psys.fill_pos_vel()
#broadcast vectors here


psys.force()
psys.ekin_f()


if psys.rank==0:
  print("Starting simulation with %d atoms for %d steps.\n" % (psys.natoms, psys.nsteps));
  print("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
  psys.output()

psys.nfi=1

for i in range(psys.nsteps):
    if psys.rank==0:
      if psys.nfi % psys.nprint == 0:
        psys.output()
    psys.nfi+=1
    psys.velverlet()
    psys.ekin_f()
    
if psys.rank==0:
  print("Simulation Done.\n");

#closes files and finalizes mpi if needed  
psys.finalize()  
  
