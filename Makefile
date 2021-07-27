# ish makefile
# 2021-07-27 19:21
# by Ian D Brunton <iandbrunton at gmail dot com>

APPNAME=ish
VERSION=0.1a
CC=gcc

#HFILES = builtins.h
HFILES =
CFILES = main.c

SRCS = $(HFILES) $(CFILES)
OBJS = $(CFILES:.c=.o)

all: $(APPNAME)

$(APPNAME): #$(OBJS)
	$(CC) $(CFLAGS) $(CFILES) -o $(APPNAME)
	#$(CC) $(LDFLAGS) -Wl,--start-group $(OBJS) -Wl,--end-group -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(APPNAME)
