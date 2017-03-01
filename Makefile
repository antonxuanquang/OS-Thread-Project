###########################################################
#
# Simple Makefile for Operating Systems Project 1
# tcush
#
# (C Version)
#
###########################################################
.SUFFIXES: .h .c .l .o

CC = gcc
CFLAGS = -w -g
LEX = flex
LIBS = -lfl -lpthread 
RM = /bin/rm
RMFLAGS = -f

OSP2A = osp2a
OSP2A_OBJS = osp2a.o

OSP2B = osp2b
OSP2B_OBJS = osp2b.o


all: osp2a osp2b

osp2a: $(OSP2A_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

osp2b: $(OSP2B_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(RMFLAGS) *.o osp2a osp2b
