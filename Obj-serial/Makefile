# -*- Makefile -*-
SPATH=../src
IPATH=../include
RPATH=..
OBJS = ljmd.o compute_forces.o helper.o kinetic.o output.o velocity.o
EXE = $(RPATH)/ljmd.x
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3
LDFLAGS=-lm -L. -g


default: $(EXE)

.PHONY: default

$(EXE): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

ljmd.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/output.h $(IPATH)/velocity.h

compute_forces.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
helper.o: $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
kinetic.o: $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/constants.h
output.o: $(IPATH)/output.h $(IPATH)/md_struct.h $(IPATH)/constants.h
velocity.o: $(IPATH)/velocity.h $(IPATH)/compute_forces.h $(IPATH)/md_struct.h $(IPATH)/constants.h


clean:
	rm -f $(OBJS) $(EXE)

.PHONY: clean


