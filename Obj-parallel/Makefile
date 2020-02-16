# -*- Makefile -*-
SPATH=../src
IPATH=../include
RPATH=..
OBJS = $(RPATH)/ljmd.o $(SPATH)/compute_forces.o  $(SPATH)/helper.o  $(SPATH)/kinetic.o  $(SPATH)/output.o  $(SPATH)/velocity.o $(SPATH)/read_input.o $(SPATH)/getline.o
EXE = $(RPATH)/ljmd-parallel.x

MPIC = mpicc


CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3
LDFLAGS=-lm -L. -g -L/opt/openmpi/4.0.1/lib 


default: $(EXE)

.PHONY: default

$(EXE): $(OBJS)
	$(MPIC) $^ -o $@ $(LDFLAGS) -DUSE_MPI

%.o: %.c
	$(MPIC) -c $(CFLAGS) $< -o $@ -DUSE_MPI

ljmd.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/output.h $(IPATH)/velocity.h $(IPATH)/read_input.h $(IPATH)/getline.h

$(SPATH)/getline.o: $(IPATH)/getline.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/read_input.o: $(IPATH)/read_input.h $(IPATH)/getline.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/compute_forces.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/helper.o: $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/kinetic.o: $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/output.o: $(IPATH)/output.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/velocity.o: $(IPATH)/velocity.h $(IPATH)/compute_forces.h $(IPATH)/md_struct.h $(IPATH)/constants.h

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: clean

ljmd.o: ljmd.c
