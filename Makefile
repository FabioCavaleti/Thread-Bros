CC = g++
BINARY = ./bin/jogo
INCLUDES = ./includes/
SRC = ./src/*.cpp
OPTIONS = -Wall -g -lpthread
VFLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all --main-stacksize=8388608

all:
	@$(CC) $(SRC) -o $(BINARY) -I$(INCLUDES) $(OPTIONS)

run:
	@$(BINARY)

valgrind:
	valgrind $(VFLAGS) $(BINARY)

clean:
	rm ./bin/*