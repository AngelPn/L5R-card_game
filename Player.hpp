//file:Player.hpp
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <list>
#include <vector>

#include "DeckBuilder.hpp"

#define NO_HAND 6
#define NO_PROVINCES 4

using namespace std;

class Player{
private:
	DeckBuilder deck;
	list<GreenCard*>* fateDeck;
	list<BlackCard*>* dynastyDeck;
	vector<GreenCard*> hand;
	vector<Holding*> holdings;
	vector<Personality*> army;
	vector<int> arena; //vector arena keeps track of army's indexes that are set for battle
	int numberOfProvinces= NO_PROVINCES;
	vector<BlackCard*> provinces;

public:
	Player();
	~Player();

	int give_no_provinces();

	void startingPhase();
	void battlePhase(Player *p);
	void untapEverything();
	void drawFateCard();
	void revealProvinces();
	void printGameStatistics();
	void printHand() const;
	void printProvinces() const;

};

#endif