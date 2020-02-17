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
LIBS= $(SRCS:%.c=$(SOPATH)/%.so)
LIBS_MPI= $(SRCS:%.c=$(SOPATH)/%.mpi.so)
LIBS_OPN= $(SRCS:%.c=$(SOPATH)/%.opn.so)
LIBS_MPI_OPN= $(SRCS:%.c=$(SOPATH)/%.mpi.opn.so)
CC = clang
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3 
LDFLAGS=-lm -L. -g 
OMPFLAGS=-fopenmp -D_OPENMP
MPIC = mpicc

default: $(EXE)

.PHONY: default

$(EXE): $(OBJS_ex)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OPATH)/%.n.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@ 
	
shared: $(LIBS)

$(LIBS): $(OBJS_so) 
	$(CC) $^ -o $@ $(LDFLAGS) -shared -fPIC -flto -fno-semantic-interposition

$(OPATH)/%.so.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC -flto -fno-semantic-interposition $< -o $@ 

.PHONY: shared

mpi: $(OBJS_mpi) $(HEADERS)
	$(MPIC) $^ -o $(EXE) $(LDFLAGS) -DUSE_MPI # -L/opt/openmpi/4.0.1/lib 

$(OPATH)/%.mpi.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -DUSE_MPI $< -o $@ 

.PHONY: mpi	
openmp: $(OBJS_opn) $(HEADERS)
	$(CC) $^ -o $(EXE) $(LDFLAGS) -fopenmp

$(OPATH)/%.opn.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $(OMPFLAGS) $< -o $@ 

.PHONY: openmp	

mpi_openmp: $(OBJS_mpi_opn) $(HEADERS)
	$(MPIC) $^ -o $(EXE) $(LDFLAGS) -fopenmp

$(OPATH)/%.mpi.opn.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) $(OMPFLAGS) -DUSE_MPI  $< -o $@ 

.PHONY: mpi_openmp
	
shared_mpi: $(LIBS_MPI)

$(LIBS_MPI): $(OBJS_mpi_so) $(HEADERS)
	$(MPIC) $^ -o $@ $(LDFLAGS) -shared -fPIC -flto -fno-semantic-interposition

$(OPATH)/%.mpi.so.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -fPIC -flto -fno-semantic-interposition -DUSE_MPI $< -o $@ 

.PHONY: shared_mpi	

shared_openmp: $(LIBS_OPN)

$(LIBS_OPN): $(OBJS_opn_so) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS) -shared -fPIC -flto -fno-semantic-interposition -fopenmp

$(OPATH)/%.opn.so.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC -flto -fno-semantic-interposition $(OMPFLAGS) $< -o $@ 

.PHONY: shared_openmp
	
shared_mpi_openmp: $(LIBS_MPI_OPN)

$(LIBS_MPI_OPN): $(OBJS_mpi_opn_so) $(HEADERS)
	$(MPIC) $^ -o $@ $(LDFLAGS) -shared -fPIC -flto -fno-semantic-interposition -fopenmp

$(OPATH)/%.mpi.opn.so.o: %.c $(HEADERS)
	$(MPIC) -c $(CFLAGS) -fPIC -flto -fno-semantic-interposition $(OMPFLAGS) -DUSE_MPI $< -o $@ 

.PHONY: shared_mpi_openmp
	
clean:
	rm -f $(OBJS_ex) $(EXE) $(LIBS) $(OBJS_mpi) $(OBJS_so) $(OBJS_mpi_so) $(OBJS_opn_so) $(OBJS_mpi_opn_so) $(OBJS_opn) $(OBJS_mpi_opn) 
	
.PHONY: clean 
