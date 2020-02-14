# -*- Makefile -*-
IPATH=../include
OPATH=../Obj-serial
SOPATH=../lib
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=$(OPATH)/%.o)
HEADERS = $(wildcard $(IPATH)/*.h)
EXE = ../ljmd.x
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3
LDFLAGS=-lm -L. -g

default: $(EXE)

.PHONY: default

$(EXE): $(OBJS) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OPATH)/%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@ 

clean:
	rm -f $(OBJS) $(EXE)

.PHONY: clean
 
