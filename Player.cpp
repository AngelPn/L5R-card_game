//file:Player.cpp
#include "Player.hpp"
#include "Card.hpp"
#include <iostream>

using namespace std;

Player::Player(const std::string &name){
	this->name = name;
	list<GreenCard*>* ptr = deck.createFateDeck();
	fateDeck= new list<GreenCard*>(*ptr);  //fateDeck is pointer to a new list of pointers which refer to the green cards in deck
	deck.deckShuffler(fateDeck);

	list<BlackCard*>* ptr1 = deck.createDynastyDeck();
	dynastyDeck = new list<BlackCard*>(*ptr1); //dynastyDeck is pointer to a new list of pointers which refer to the black cards in deck
	deck.deckShuffler(dynastyDeck);

	for(int i=0; i< NO_HAND; i++){
		hand.push_back(fateDeck->front());
		fateDeck->pop_front();
  }

	holdings.push_back(new Stronghold);
	money = holdings[0]->initialMoney();
	numberOfProvinces= NO_PROVINCES;

	for(int i=0; i< numberOfProvinces; i++){
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

void Player::printGameStatistics(){
	cout<< "Number of Holdings: "<< this->holdings.size()<< endl;
	cout<< "Number of Personalities in Army: "<< this->army.size()<< endl;
	cout<< "Number of Provinces: "<< this->provinces.size()<< endl;
}

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

void Player::equipPhase()
{
	cout << "Player: " << this->name << " is playing " << endl;
	cout << "Equip Phase ..." << endl << endl;
	//player prints hand and army if has any
	if (!army.size())
	{
		cout << "No army found, phase is skipped :(" << endl << endl;
		return;
	}
	else if (!money)
	{
		cout << "No money available, phase is skipped :(" << endl << endl;
		return;
	}

	else //proceed only if army and money are both available
	{
		this->printHand();
		this->printArmy();
	}

	char input = '0';
	unsigned int soldier = 0, card = 0;

	while(money)  //while player has money and wants to
	{
		cout << "Available money : " << money << endl << endl;
		while (input != 'y' && input != 'n')
		{
			cout << "Do you want buy any cards from your hand (y:yes / n:no) ?" << endl;
			cin >> input;
		}

		if (input == 'n')
		{
			cout << "Well, okay then, get ready for battle phase" << endl << endl;
			return; //exit equip phase
		}

		while (soldier < 1 || soldier > army.size())
		{
			cout << "Choose a personality of your army to equip: (1-" << army.size() << ")" << endl;
			cin >> soldier;
		}

		//if the upper bound of green cards for the personality is  exceeded
		if (army[soldier-1]->belowBound() == false)
		{
			cout << "Personality already has max green cards, purchase cancelled" << endl;
			continue;
		}

		while (card < 1 || card > hand.size())
		{
			cout << "Choose a card in your hand to equip selected personality with : (1-" << hand.size() << ")" << endl;
			cin >> card;
		}

		//if money is not enough for purchase
		if (hand[card-1]->get_cost() > money)
		{
			cout << "Selected card cannot be afforded, purchase cancelled" << endl;
			continue;
		}

		//if minimum honour of selected card is not matched by honour of selected personality
		if (hand[card-1]->get_honour() > army[soldier-1]->get_honour())
		{
			cout << "Selected card's honour is too high for your selected soldier, purchase cancelled" << endl;
			continue;
		}

		//at this point purchase is made
		money -= hand[card-1]->get_cost();   //make purchase
		//assign card (item or follower) to personality
		army[soldier-1]->equip(hand[card-1]);
		cout << "Purchase successfully made, card was assigned to your soldier " << endl << endl;
		//if player has available money to buy the effect cost of card
		if (hand[card-1]->get_effectCost() <= money)
		{
			input = '0';
			while (input != 'y' && input != 'n')
			{
				cout << "Do you want buy the effect bonus of the card (y:yes / n:no) ?" << endl;
				cin >> input;
			}

			if (input == 'y')
			{
				money -= hand[card-1]->get_effectCost(); //make purchase
				//apply effectBonus to card
				hand[card-1]->applyBonus();
				cout << "Purchase successfully made,effect bonus of card applied " << endl << endl;
			}
		}

		//add attack/defense bonuses of card directly to soldier (this can be done either here or in battle phase)
		army[soldier-1]->applyBonus(hand[card-1]);

		hand.erase(hand.begin() + (card-1)); //erase card from hand

	}
}

void Player::printArmy() const
{
	cout << "Printing army : " << endl << endl;
	for (vector<Personality*>::const_iterator it = army.begin(); it != army.end(); ++it)
	{
		(*it)->print();
	}
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
