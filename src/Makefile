# -*- Makefile -*-
IPATH=../include
OPATH=../Obj-serial
SOPATH=../lib
SRCS = $(wildcard *.c)
OBJS_ex = $(SRCS:%.c=$(OPATH)/%.n.o)
OBJS_so = $(SRCS:%.c=$(OPATH)/%.so.o)
HEADERS = $(wildcard $(IPATH)/*.h)
EXE = ../ljmd.x
LIBS= $(SRCS:%.c=$(SOPATH)/%.so)
CC = gcc
CFLAGS = -I $(IPATH) -Wall -Wextra -ffast-math -fomit-frame-pointer -O3 
LDFLAGS=-lm -L. -g 

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


clean:
	rm -f $(OBJS) $(EXE) $(LIBS)
	
.PHONY: clean
 
