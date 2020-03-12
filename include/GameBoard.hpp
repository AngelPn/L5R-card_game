#include <iostream>
#include <vector>

#include "Player.hpp"

using namespace std;

class GameBoard{
private:
	vector<Player*> players;

public:

	~GameBoard();

	void initializeGameBoard(int no_players= 2);
	void printGameStatistics();
	int checkWinningCondition();
	void gameplay();
};
