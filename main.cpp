#include <iostream>
#include "cstdio"
#include "GameBoard.hpp"

int main(void){
	GameBoard Legend_of_5_Rings;
	std::cout<< "How many players? Type a number: (2-8): ";
	int c= getchar();
	putchar(c);
	std::cout<< std::endl;
	Legend_of_5_Rings.initializeGameBoard(c);
	//Legend_of_5_Rings.gameplay();

	return 0;
}
