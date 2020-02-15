//file:Player.cpp
#include "Player.hpp"
#include "Card.hpp"
#include <iostream>

using namespace std;

Player::Player(){
	list<GreenCard*>* ptr = deck.createFateDeck();
	fateDeck= new list<GreenCard*>(*ptr);  //fateDeck is pointer to a new list of pointers which refer to the green cards in deck
	deck.deckShuffler(fateDeck);

	list<BlackCard*>* ptr1 = deck.createDynastyDeck();
	dynastyDeck = new list<BlackCard*>(*ptr1); //dynastyDeck is pointer to a new list of pointers which refer to the black cards in deck

	for(int i=0; i< NO_HAND; i++){
		hand.push_back(fateDeck->front());
		fateDeck->pop_front();
    }

	holdings.push_back(new Stronghold);

	numberOfProvinces= 4;
	for(int i=0; i< NO_PROVINCES; i++){
		provinces.push_back(dynastyDeck->front());
		dynastyDeck->pop_front();  	
	}
}

Player::~Player(){
	dynastyDeck->clear();
	delete dynastyDeck;
	fateDeck->clear();
	delete fateDeck;
	delete holdings[0]; //deletes stronghold
	//deck and the cards get  deleted by destructor of class DeckBuilder
}

int Player::give_no_provinces(){ return numberOfProvinces; }

void Player::startingPhase() 
{
	cout << "Starting Phase ..." << endl << endl;
	this->untapEverything(); //untap all cards
	this->drawFateCard(); //draw top card of fateDeck
	this->revealProvinces(); //reveal not-destroyed provinces
	this->printHand(); //print cards in your hand
	this->printProvinces(); //prints not-destroyed provinces
}

void Player::untapEverything()
{
	for (vector<GreenCard *>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		(*it)->untap();
	}

	for (vector<Holding*>::iterator it = holdings.begin(); it != holdings.end(); ++it)
	{
		(*it)->untap();
	}

	for (vector<Personality*>::iterator it = army.begin(); it != army.end(); ++it)
	{ 
		(*it)->untap();
	}

	for (vector<BlackCard*>::iterator it = provinces.begin(); it != provinces.end(); ++it)
	{
		(*it)->untap();
	}

	cout << "All cards untapped " << endl << endl;
}

void Player::drawFateCard()
{
	hand.push_back(fateDeck->front());  //push card from front of the fate deck to hand
	fateDeck->pop_front(); //pop the first card of the fateDeck
}

void Player::revealProvinces()
{
	for (vector<BlackCard*>::iterator it = provinces.begin(); it != provinces.end(); ++it)
	{
		(*it)->reveal();
	}

	cout << "Provinces revealed " << endl << endl;
}

void Player::battlePhase(Player *p){
	vector<int> untapped_army; //vector of army's indexes that keeps track of untapped personalities in army
	for(int i=0; i< army.size(); i++){
		if(!army[i]->isTapped())
			untapped_army.push_back(i);
	}
	cout<< "Choose the number of untapped Personalities from Army to defense/battle: "<< endl<<
		"The number of existing untapped Personalities in Army is "<< untapped_army.size()<< endl<<
		"Type a number from 0 to "<< untapped_army.size()-1<< ": ";
	int c= getchar();
	putchar(c);
	//Built up the arena
	for(int i=0; i< c; i++)
			arena.push_back(i);
	
	if(p!= NULL){ //If the player has chosen battle
		//Calculate the total points of attacker and defender
		int points_attacker= 0, points_defender= 0;
		for(int i= 0; i< arena.size(); i++)
			points_attacker+= army(arena[i])->get_defense();
		for(int i= 0; i< p->arena.size(); i++)
			points_defender+= p->army(arena[i])->get_defense();

		int province_defense= p->holdings[0].get_initialDefense(); //Get the defense's point from StrongHold
		//TO DO: add the defense of personality
		points_defender+= province_defense;
		if(points_attacker - points_defender > province_defense){ //Attacker wins the battle
			p->provinces.erase(0); //Destroy defender's province
			p->numberOfProvinces--; //Decrement defender's total number of provinces
			//Defender looses all of the defensive personalities
			for(int i=0; i< p->arena.size(); i++)
				p->army.erase(arena[i]);
			p->arena.clear();
		}
		else{
			if(points_attacker > points_defender){ 
				//Defender looses all of the defensive personalities
				for(int i=0; i< p->arena.size(); i++)
					p->army.erase(arena[i]);
				p->arena.clear();
				//Attacker looses followers or personalities from arena's army that attack>= points_attacker- points_defender
				int lost_points= 0;
				while(lost_points < (points_defender - points_defender)){
					
				}
			}
			else if(points_attacker == points_defender){

			}
			else{

			}
		}
	}
}

void Player::printGameStatistics(){
	cout<< "Number of Holdings: "<< this->holdings.size()<< endl;
	cout<< "Number of Personalities in Army: "<< this->army.size()<< endl;
	cout<< "Number of Provinces: "<< this->provinces.size()<< endl;
}

void Player::printHand() const
{
	cout << "Printing cards in hand : " << endl << endl;
	for (vector<GreenCard *>::const_iterator it = hand.begin(); it != hand.end(); ++it)
	{
		(*it)->print();
	}
}

void Player::printProvinces() const
{
	cout << "Printing provinces : " << endl << endl;
	for (vector<BlackCard*>::const_iterator it = provinces.begin(); it != provinces.end(); ++it)
	{
		(*it)->print();
	}

}