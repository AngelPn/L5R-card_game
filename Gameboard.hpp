#include <iostream>
#include <vector>

#include "Player.hpp"

class GameBoard{
private:
	vector<Player*> players;

public:

	~GameBoard();

	void initializeGameBoard(int no_players);
	void printGameStatistics();
	int checkWinningCondition();
	void gameplay();
};