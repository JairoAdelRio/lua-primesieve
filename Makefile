# Makefile for primesieve

TOPDIR= /usr/local
INCDIR= $(TOPDIR)/include
BINDIR= $(TOPDIR)/bin
LIBDIR= $(LUA_TOPDIR)/lib/lua/5.4

LUA= $(BINDIR)/lua

CC= gcc
CFLAGS= -Wall -Wextra -Wfatal-errors -O2
MYCFLAGS=

MYNAME= primesieve
MYFILE= l$(MYNAME).c
MYMOD= $(MYNAME).$(LIBEXT)

all:	build test

test:
	$(LUA) test.lua

build:
	$(CC) $(CFLAGS) $(MYCFLAGS) -shared -fPIC -o $(MYMOD) $(MYFILE) $(LIBFLAG)

install:
	cp $(MYMOD) $(LIBDIR)

clean:
	rm $(MYMOD)

LIBFLAG=-llua -lprimesieve
LIBEXT= so

.PHONY: all test build install clean