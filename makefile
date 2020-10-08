CC=gcc
CFLAGS=-std=c89 -pedantic -Wall -Werror -g
LDFLAGS=`xml2-config --cflags`
LDLIBS=`xml2-config --libs`
RM=rm -fv
.PHONY: all clean
all : ddgm.out

%.o: %.c %.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

ddgm.out: ddgm.c ddg.o player.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) *.o *.out
