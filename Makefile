#paths
INCLUDE = ./include
SRC = ./src

#compiler
CC = g++

#compile options
CPPFLAGS = -Wall -g -I$(INCLUDE)

OBJS = $(SRC)/main.o $(SRC)/DeckBuilder.o $(SRC)/GameBoard.o $(SRC)/TypeConverter.o \
			$(SRC)/Personality.o $(SRC)/Player.o

EXEC = L5R

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)