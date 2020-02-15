# -*- Makefile -*-
IPATH=../include
OPATH=../Obj-serial
SOPATH=../lib
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=$(OPATH)/%.o)
HEADERS = $(wildcard $(IPATH)/*.h)
EXE = ../ljmd.x
LIBS= $(SRCS:%.c=$(SOPATH)/%.so)
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3
LDFLAGS=-lm -L. -g

default: $(EXE)

.PHONY: default

$(EXE): $(OBJS) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OPATH)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@ 
	
shared: $(LIBS)

$(LIBS): $(OBJS) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS) -shared 

$(OPATH)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -fPIC $< -o $@ 


clean:
	rm -f $(OBJS) $(EXE) $(LIBS)
	
.PHONY: clean
 
