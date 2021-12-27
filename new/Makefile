CC = g++
LIBS = -Wall -Wextra -Wpedantic -pedantic-errors
CFLAGS = -g -Wall -lpthread
VFLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all --main-stacksize=8388608
BINARY = ./jogo
SRC = main.cpp puzzle.cpp
DEP = main.o puzzle.o

all: $(SRC) $(DEP)
	$(CC) $(DEP) $(CFLAGS) -o $(BINARY) 

run:
	$(BINARY)

valgrind:
	valgrind $(VFLAGS) $(BINARY)

clean:
	rm -rf $(DEP) $(BINARY)