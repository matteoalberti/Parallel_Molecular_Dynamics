# -*- Makefile -*-
IPATH=../include
OPATH=../Obj-serial
SOPATH=../lib
SRCS = $(wildcard *.c)
OBJS_ex = $(SRCS:%.c=$(OPATH)/%.n.o)
OBJS_so = $(SRCS:%.c=$(OPATH)/%.so.o)
OBJS_mpi = $(SRCS:%.c=$(OPATH)/%.mpi.o)
OBJS_opn = $(SRCS:%.c=$(OPATH)/%.opn.o)
OBJS_mpi_opn = $(SRCS:%.c=$(OPATH)/%.mpi.opn.o)
OBJS_mpi_so = $(SRCS:%.c=$(OPATH)/%.mpi.so.o)
OBJS_opn_so = $(SRCS:%.c=$(OPATH)/%.opn.so.o)
OBJS_mpi_opn_so = $(SRCS:%.c=$(OPATH)/%.mpi.opn.so.o)
HEADERS = $(wildcard $(IPATH)/*.h)
EXE = ../ljmd.x
LIB= $(SOPATH)/ljmd.so
CC = gcc

CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3  -std=c99
LDFLAGS=-lm -L. -g 
OMPFLAGS=-fopenmp #-D_OPENMP
MPIC = mpicc

default: serial

.PHONY: default

serial: $(OBJS_ex)
	$(CC) $^ -o $(EXE) $(LDFLAGS)

$(OPATH)/%.n.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@
	
.PHONY: serial
	
shared: $(OBJS_so) 
	$(CC) $^ -o $(LIB) $(LDFLAGS) -shared -fPIC -flto


$(OPATH)/%.so.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC -flto  $< -o $@

.PHONY: shared

mpi: $(OBJS_mpi) $(HEADERS)
	$(MPIC) $^ -o $(EXE) $(LDFLAGS) -DUSE_MPI #-L/opt/openmpi/4.0.1/lib

$(OPATH)/%.mpi.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -DUSE_MPI $< -o $@

.PHONY: mpi	
openmp: $(OBJS_opn)
	$(CC) $^ -o $(EXE) $(LDFLAGS) -fopenmp

$(OPATH)/%.opn.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@

.PHONY: openmp	

mpi_openmp: $(OBJS_mpi_opn)
	$(MPIC) $^ -o $(EXE) $(LDFLAGS) -fopenmp

$(OPATH)/%.mpi.opn.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) $(OMPFLAGS) -DUSE_MPI  $< -o $@

.PHONY: mpi_openmp
	

shared_mpi: $(OBJS_mpi_so) 
	$(MPIC) $^ -o $(LIB) $(LDFLAGS) -shared -fPIC -flto 

$(OPATH)/%.mpi.so.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -fPIC -flto -DUSE_MPI $< -o $@

.PHONY: shared_mpi	

shared_openmp: $(OBJS_opn_so)
	$(CC) $^ -o $(LIB) $(LDFLAGS) -shared -fPIC -flto -fopenmp

$(OPATH)/%.opn.so.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC -flto  $(OMPFLAGS) $< -o $@

.PHONY: shared_openmp
	
shared_mpi_openmp: $(OBJS_mpi_opn_so)
	$(MPIC) $^ -o $(LIB) $(LDFLAGS) -shared -fPIC -flto -fopenmp

$(OPATH)/%.mpi.opn.so.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -fPIC -flto $(OMPFLAGS) -DUSE_MPI $< -o $@

.PHONY: shared_mpi_openmp
	
clean:
	rm -f $(OBJS_ex) $(EXE) $(LIB) $(OBJS_mpi) $(OBJS_so) $(OBJS_mpi_so) $(OBJS_opn_so) $(OBJS_mpi_opn_so) $(OBJS_opn) $(OBJS_mpi_opn) 
	
.PHONY: clean
