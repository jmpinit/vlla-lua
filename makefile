PROG := vlla-lua

ifeq ($(OS),Windows_NT)
S := \\
else
S := /
endif

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES = vlla-lua.c \
	  vlla-lib.c \
	  vlla.c \
	  serial.c

INCLUDES = -Isrc$(S)inc -I/usr/local/include -I/usr/include/lua5.1
OBJECTS = $(patsubst %,$(OBJDIR)$(S)%,$(SOURCES:.c=.o))

CFLAGS := -Wall -pedantic -std=gnu99 -g -Os -gstabs -ggdb -fstrict-aliasing
LFLAGS = -lm -lpthread -L/usr/local/lib -llua5.1
CC := gcc

all: $(PROG)

run: $(PROG)
	bin$(S)$(PROG)
	
debug: $(PROG)
	gdb bin$(S)$(PROG)

# linking the program.
$(PROG): $(OBJECTS) $(BINDIR)
	$(CC) $(OBJECTS) -o $(BINDIR)$(S)$(PROG) $(LFLAGS)

$(BINDIR):
	mkdir -p $(BINDIR)

# compiling source files.
$(OBJDIR)$(S)%.o: $(SRCDIR)$(S)%.c $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -s -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
ifeq ($(OS),Windows_NT)
	del $(OBJECTS)
else
	rm $(OBJECTS)
endif

.PHONY: all clean

