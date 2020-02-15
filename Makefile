OBJS= main.o DeckBuilder.o Player.o GameBoard.o
CFLAGS = -g -Wall -I.
PROGRAM= ex

$(PROGRAM): clean $(OBJS)
	g++ -g $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)