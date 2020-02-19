# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
OBJ_PARALLEL=$(SRC:src/%.f90=Obj-parallel/%.o)
nprocs=2
############################################

default: serial

serial:
	$(MAKE) $(MFLAGS) -C src

clean:
	$(MAKE) $(MFLAGS) -C src clean
	$(MAKE) $(MFLAGS) -C examples clean

check: 
	$(MAKE) $(MFLAGS) -C examples check

check_c: 
	$(MAKE) $(MFLAGS) -C examples check_c
	
mpi_check:
	$(MAKE) $(MFLAGS) -C examples mpi_check nprocs=$(nprocs)
	
mpi_check_c:
	$(MAKE) $(MFLAGS) -C examples mpi_check_c nprocs=$(nprocs)

		
test:
	$(MAKE) $(MFLAGS) -C testing all_py
	
shared: 
	$(MAKE) $(MFLAGS) -C src shared  
	
shared_mpi: 
	$(MAKE) $(MFLAGS) -C src shared_mpi  

shared_openmp: 
	$(MAKE) $(MFLAGS) -C src shared_openmp  

shared_mpi_openmp: 
	$(MAKE) $(MFLAGS) -C src shared_mpi_openmp
	
mpi: 
	$(MAKE) $(MFLAGS) -C src mpi

openmp:
	$(MAKE) $(MFLAGS) -C src openmp

mpi_openmp:
	$(MAKE) $(MFLAGS) -C src mpi_openmp
