# Project

Simulation of the trading cards game "Legend of the Five Rings".

# Compilation and Execution

Type the following commands inside the directory project:

    • make run: compile & run
    • make clean: clean the directory
    • make: compile only

# Project Structure

    • Card.hpp: contains the definition of classes Card, GreenCard, BlackCard
    • Follower.hpp: definition of class Follower and subclasses of it.
    • Item.hpp: definition of class Item and subclasses of it.
    • Holding.hpp: definition of class Holding and subclasses of it.
    • Personality.*: definition of class Personality and subclasses of it.
    • Player.*: definition of class Player.
    • GameBoard.*: definition of class GameBoard.
    • DeckBuilder.*: definition of class DeckBuilder.
    • TypeConverter.*: definition of class TypeConverter.

# How to play

The game’s rule guides can be found in the file "OOPproj_2020.pdf". For the official rule guides follow this link:
https://www.fantasyflightgames.com/en/products/legend-of-the-five-rings-the-card-game/ .
The users of the program, as players, determine the course of the game through their choices. It’s up to the users to find the right strategy in order to win. The game’s control of the flow and phase switching is done automatically by the program. At the start of the game, the user gives the number of the players and their names. During execution of the program, suitable messages are printed to determine the phase of the game, the player’s turn, the player’s cards and the choices he/she can make through questions. Input the right answers and have fun!

# NOTE

Even though there are places in the code where we have tried to incorporate error handling, such as carefully chosen error diagnostic messages and out of bounds checks, there could be places where error checking is absent from the code. Please be careful with that. The questions formulate the inputs that can be given.

# Classes hierachy

                    Card
                /       	\
         GreenCard 	    	    BlackCard
        /		\	    	    /		\
    Follower 	Item	Holding 	Personality
       |	    	|		|	    	|
      {…}	    	{…}		{…}	    	{…}

 # Authors

    • Vasilis Vasilakis
    • Angeliki Panagopoulou
