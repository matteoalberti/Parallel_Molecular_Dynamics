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

check: serial
	$(MAKE) $(MFLAGS) -C examples check
	
test:
	$(MAKE) $(MFLAGS) -C testing test
	
shared: 
	$(MAKE) $(MFLAGS) -C src shared  
