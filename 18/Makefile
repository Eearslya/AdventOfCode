CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
BINARY=prgm

all: $(SOURCES) $(BINARY) cleanobj

$(BINARY): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(BINARY)

cleanobj:
	rm $(OBJECTS)
