CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -std=c++11
SOURCES=readboard.cpp main.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=AStar

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o