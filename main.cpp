#include <iostream>
#include "Gameboard.hpp"

int main(void){
	GameBoard Legend_of_5_Rings;
	cout<< "How many players? Type a number: (2-8): "
	int c= getchar();
	putchar(c);
	Legend_of_5_Rings.initializeGameBoard(c);
	//Legend_of_5_Rings.gameplay();

	return 0;
}
