# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
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
test:
	$(MAKE) $(MFLAGS) -C testing test
	
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
	
	
