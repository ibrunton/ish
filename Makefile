# ish makefile
# 2021-07-27 19:21
# by Ian D Brunton <iandbrunton at gmail dot com>

APPNAME = ish
VERSION = 0.1a
CC = gcc

CFLAGS = -DVERSION=\"$(VERSION)\" -DAPPNAME=\"$(APPNAME)\" -I.

SRCS = main.c builtins.c
OBJS = $(SRCS:.c=.o)
DEPS = builtins.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(APPNAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o $(APPNAME)
