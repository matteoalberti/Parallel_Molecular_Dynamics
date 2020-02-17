# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
OBJ_PARALLEL=$(SRC:src/%.f90=Obj-parallel/%.o)
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
	$(MAKE) $(MFLAGS) -C src clean
	
mpi: 
	$(MAKE) $(MFLAGS) -C src mpi
check: serial
	$(MAKE) $(MFLAGS) -C examples check

check-parallel: parallel
	$(MAKE) $(MFLAGS) -C examples parallel
	
test:
	$(MAKE) $(MFLAGS) -C testing test
