# -*- Makefile -*-
SPATH=../src
IPATH=../include
RPATH=..
OBJS = $(RPATH)/ljmd.o $(SPATH)/compute_forces.o  $(SPATH)/helper.o  $(SPATH)/kinetic.o  $(SPATH)/output.o  $(SPATH)/velocity.o
EXE = $(RPATH)/ljmd.x
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3
LDLIBS=-lm


default: $(EXE)

.PHONY: default

$(EXE): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(LDLIBS) $< -o $@

ljmd.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/output.h $(IPATH)/velocity.h

$(SPATH)/compute_forces.o: $(IPATH)/compute_forces.h $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/helper.o: $(IPATH)/helper.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/kinetic.o: $(IPATH)/kinetic.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/output.o: $(IPATH)/output.h $(IPATH)/md_struct.h $(IPATH)/constants.h
$(SPATH)/velocity.o: $(IPATH)/velocity.h $(IPATH)/compute_forces.h $(IPATH)/md_struct.h $(IPATH)/constants.h


clean:
	rm -f $(OBJS) $(EXE)

.PHONY: clean

# dependencies)
ljmd.o: ljmd.c

