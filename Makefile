# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
OBJ_PARALLEL=$(SRC:src/%.f90=Obj-parallel/%.o)4
nprocs=1
############################################

default: serial

serial:
	$(MAKE) $(MFLAGS) -C Obj-serial

parallel:
	$(MAKE) $(MFLAGS) -C Obj-parallel

clean:
	$(MAKE) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C Obj-parallel clean
	$(MAKE) $(MFLAGS) -C examples clean

check: serial
	$(MAKE) $(MFLAGS) -C examples check

mpi_check: parallel
	$(MAKE) $(MFLAGS) -C examples mpi_check nprocs=$(nprocs)
	
test:
	$(MAKE) $(MFLAGS) -C testing test
