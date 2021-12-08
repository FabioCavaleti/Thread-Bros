#Makefile básico para a execução do projeto
CC=g++
LIBS=-Wall -Wextra -Wpedantic -pedantic-errors
CFLAGS=-c -g -O0
VFLAGS=--leak-check=full --track-origins=yes --show-leak-kinds=all --main-stacksize=8388608
BINARY=./jogo
SRC = jogo_trabalho.cpp maps.cpp
DEP =  jogo_trabalho.o maps.o

all: $(SRC) $(DEP)
	$(CC) $(DEP) -o $(BINARY) 


run:
	$(BINARY)

valgrind:
	valgrind $(VFLAGS) $(BINARY)

clear:
	rm -rf $(DEP) $(BINARY)