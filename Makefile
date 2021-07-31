# ish makefile
# 2021-07-27 19:21
# by Ian D Brunton <iandbrunton at gmail dot com>

APPNAME=ish
VERSION=0.1a
CC=gcc

CFLAGS = -c -g -Wall -DVERSION=\"$(VERSION)\" -DAPPNAME=\"$(APPNAME)\"

HFILES = builtins.h
CFILES = main.c builtins.c

SRCS = $(HFILES) $(CFILES)
OBJS = $(CFILES:.c=.o)

all: $(APPNAME)

$(APPNAME): 
	$(CC) $(LDFLAGS) -Wl,--start-group $(OBJS) -Wl,--end-group -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(APPNAME)
