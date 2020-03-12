#include <iostream>
#include "GameBoard.hpp"

int main(void){
	GameBoard Legend_of_5_Rings;
	std::cout<< "How many players? Type a number: (2-8): ";
	int no_players= 0;
	while(no_players< 2 || no_players> 8){
		std::cin>> no_players;
		std::cout<< std::endl;
	}
	Legend_of_5_Rings.initializeGameBoard(no_players);
	Legend_of_5_Rings.gameplay();

	return 0;
}
