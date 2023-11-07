CC= gcc
CFLAGS= -Wall -Werror -Wextra -pedantic
CFILES= $(wildcard *.c)
DEBUGFLAGS= -g
PROGNAME= hsh

all: prog

prog: $(CFILES)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(CFILES) -o $(PROGNAME)