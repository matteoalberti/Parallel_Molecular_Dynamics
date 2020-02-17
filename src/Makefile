# -*- Makefile -*-
IPATH=../include
OPATH=../Obj-serial
SOPATH=../lib
SRCS = $(wildcard *.c)
OBJS_ex = $(SRCS:%.c=$(OPATH)/%.n.o)
OBJS_so = $(SRCS:%.c=$(OPATH)/%.so.o)
OBJS_mpi = $(SRCS:%.c=$(OPATH)/%.mpi.o)
HEADERS = $(wildcard $(IPATH)/*.h)
EXE = ../ljmd.x
EXE_MPI=../ljmd.x
LIBS= $(SRCS:%.c=$(SOPATH)/%.so)
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3 
LDFLAGS=-lm -L. -g 
MPIC = mpicc

default: $(EXE)

.PHONY: default

$(EXE): $(OBJS_ex) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OPATH)/%.n.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@ 
	
shared: $(LIBS)

$(LIBS): $(OBJS_so) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS) -shared -fPIC -flto -fno-semantic-interposition

$(OPATH)/%.so.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC -flto -fno-semantic-interposition $< -o $@ 

mpi: $(EXE_MPI)

$(EXE_MPI): $(OBJS_mpi) $(HEADERS)
	$(MPIC) $^ -o $@ $(LDFLAGS) -DUSE_MPI # -L/opt/openmpi/4.0.1/lib 

$(OPATH)/%.mpi.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -DUSE_MPI $< -o $@ 
	
clean:
	rm -f $(OBJS_ex) $(EXE) $(LIBS) $(OBJS_mpi) $(OBJS_so) 
	
.PHONY: clean 
