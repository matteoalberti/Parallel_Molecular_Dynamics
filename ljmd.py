import mdsys_struct as md
import time

#calling the system variable "sys" would be confusing as "sys" is a rather standart module, so we call it psys
psys=md.mdsys()

#initialize MPI if defined and get rank, rank zero if MPI not defined
psys.initial()

psys.read_input()

psys.broadcast_vals()

psys.alloc_ptrs()

#allocate extra buffers if MPI defined
psys.extra_alloc()

if psys.rank==0:
  psys.fill_pos_vel()

psys.broadcast_arrs()

psys.force()
if psys.rank==0:
  psys.ekin_f()

if psys.rank==0:
  print("Starting simulation with %d atoms for %d steps.\n" % (psys.natoms, psys.nsteps));
  print("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
  psys.output()
  start = time.time()

psys.nfi=1

for i in range(psys.nsteps):
    if psys.rank==0:
      if psys.nfi % psys.nprint == 0:
        psys.output()
    psys.nfi+=1
    if psys.rank==0:
      psys.vel1()
    psys.force()
    if psys.rank==0:
      psys.vel2()
      psys.ekin_f()
 
#print(psys.rank);   
   
if psys.rank==0:
  print("Simulation Done.\n");
  psys.close_files()
  end = time.time()
  print(end-start)

  
psys.extra_free()


#finalizes mpi if needed  
psys.finalize()  
