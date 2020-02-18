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
	cout << "Player: " << this->name << " is playing " << endl;
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
	cout << "Drew fate card " << endl << endl;
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
		if ((*it)->is_revealed() == true)
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
	else if (!money && holdings.size() == 1)
	{
		cout << "No money and holdings available (you're broke dude), phase is skipped :(" << endl << endl;
		return;
	}

	else //proceed only if army and money are both available
	{
		cout << "Available money : " << money << endl << endl;
		this->printHand();
		this->printArmy();
	}

	this->tapHoldings(); //tap any holdings in case you need money

	char input;
	unsigned int soldier = 0, card = 0;

	while(money)  //while player has money and wants to
	{
		input = '0';
		soldier=0;
		card = 0;
		cout << "Available money : " << money << endl << endl;
		while (input != 'y' && input != 'n')
		{
			cout << this->name<< ", do you want to buy any cards from your hand (y:yes / n:no) ?" << endl;
			cin >> input;
		}

		if (input == 'n')
		{
			cout << "Well, okay then, get ready for battle phase" << endl << endl;
			return; //exit equip phase
		}
		while (soldier < 1 || soldier > army.size())
		{
			this->printArmy();
			cout << this->name<< ", choose a personality of your army to equip: (1-" << army.size() << ")" << endl;
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
			this->printHand();
			cout << this->name<< ", choose a card in your hand to equip selected personality with : (1-" << hand.size() << ")" << endl;
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
				cout << this->name<< ", do you want buy the effect bonus of the card (y:yes / n:no) ?" << endl;
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

bool Player::hasArmy(){
	if(!army.size()) return false;
	else return true;
}

void Player::battlePhase(Player *p){
	//All of the cards in Army are untapped because of the startingPhase
	cout<< this->name<< ", choose the number of untapped Personalities in Army to defense/battle: "<< endl<<
		"The number of existing untapped Personalities in Army is "<< army.size()<< endl<<
		"Type a number (1-"<< army.size()<< "): ";
	int c= 0;
	while(c< 1 || c> army.size()){
		cin>> c;
		cout<< c<< endl;
	}

	//Built up the arena
	printArmy();
	cout<< this->name<< ", choose which of the Personalities in Army you want in Arena: "<< endl<<
		"Type "<< c<< " different numbers: (1-"<< army.size()<< "): ";
	int n= 0;
	arena.clear(); //Clear the previous arena
	for(int i=0; i< c; i++){
		cin>> n;
		arena.push_back(n -1); //vector of army's indexes that keeps track of personalities in arena
	}
	printArena();

	if(p!= NULL){ //If the player has chosen battle

		cout<< "Enemy's provinces: "<< endl;
		p->printProvinces();
		cout<< this->name<< ", choose the enemy's province to attack: "<< endl<<
			"The number of enemy's provinces is "<< p->numberOfProvinces<< endl<<
			"Type a number: (1-"<< p->numberOfProvinces<< "): ";
		cin>> n;

		//Calculate the total points of attacker and defender
		int points_attacker= 0, points_defender= 0;

		for(int i= 0; i< arena.size(); i++)
			points_attacker+= army[arena[i]]->get_attack();

		for(int i= 0; i< p->arena.size(); i++)
			points_defender+= p->army[arena[i]]->get_defense();

		int province_defense= p->holdings[0]->get_initialDefense(); //Get the province defense points from StrongHold
		points_defender+= province_defense;

		if(points_attacker - points_defender > province_defense){ //Attacker won the battle, province is destroyed
			p->provinces.erase(provinces.begin()+ c-1); //Destroy defender's province
			p->numberOfProvinces--; //Decrement defender's total number of provinces
			//Defender loses all of the defensive personalities
			for(int i=0; i< p->arena.size(); i++)
				p->army.erase(p->army.begin()+ arena[i]);
			p->arena.clear();
			//Print a message
			cout<< "Attacker's points - Defender's points > Province's defense"<< endl<<
				"Attacker "<< this->name<< " won the battle. Enemy's province is destroyed!"<< endl<<
				"Print Enemy's provinces: "<< endl;
			p->printProvinces();
		}
		else{ //Province is not destroyed
			if(points_attacker > points_defender){
				//Defender loses all of the defensive personalities
				for(int i=0; i< p->arena.size(); i++)
					p->army.erase(p->army.begin()+ arena[i]);
				p->arena.clear();

				//Attacker loses followers or personalities from arena's army that attack>= points_attacker- points_defender
				int lost_points= 0, k= 0;
				while(lost_points < (points_defender - points_defender)){

					if(army[arena[k]]->hasFollowers()){ //If the Personality has followers
						army[arena[k]]->destroyFollower(&lost_points);
						continue;
					}
					else{
						lost_points+= army[arena[k]]->get_attack();
						army.erase(army.begin()+ arena[k]); //delete the Personality
						arena.erase(arena.begin()+ k);
					}

					if(k == army.size()) break;
					k++;
				}

				//Tap every Personality and Followers that have survived
				for(int i= 0; i< arena.size(); i++){
					army[arena[i]]->tap_followers();
					army[arena[i]]->tap();
					//Items of Personality loses one durability
					army[arena[i]]->decrement_durability();
				}
				//Print a message
				cout<< "Attacker's points - Defender's points < Province's defense"<< endl<<
					"Province is not destroyed!"<< endl<<
					"Attacker's points > Defender's points"<< endl<<
					"Defender loses all of the defensive Personalities"<< endl<<
					"Attacker loses followers or personalities from Arena's army that attack>= points_attacker- points_defender"<< endl;
			}
			else if(points_attacker == points_defender){
				//Attacker loses all of the attacking personalities and followers
				for(int i=0; i< arena.size(); i++)
					army.erase(army.begin()+ arena[i]);
				arena.clear();

				//Defender loses all of the defensive personalities and followers
				for(int i=0; i< p->arena.size(); i++)
					p->army.erase(p->army.begin()+ arena[i]);
				p->arena.clear();
				//Print a message
				cout<< "Attacker's points - Defender's points < Province's defense"<< endl<<
					"Province is not destroyed!"<< endl<<
					"Attacker's points == Defender's points"<< endl<<
					"Defender loses all of the defensive Personalities and Followers"<< endl<<
					"Attacker loses all of the attacking Personalities and Followers"<< endl;
			}
			else{
				//Attacker loses all of the attacking personalities and followers
				for(int i=0; i< arena.size(); i++)
					army.erase(army.begin()+ arena[i]);
				arena.clear();

				//Defender loses followers or personalities from arena's army that attack>= points_attacker- points_defender
				int lost_points= 0, k= 0;
				while(lost_points < (points_defender - points_defender)){

					if(p->army[arena[k]]->hasFollowers()){ //If the Personality has followers
						p->army[arena[k]]->destroyFollower(&lost_points);
						continue;
					}
					else{
						lost_points+= p->army[arena[k]]->get_attack();
						p->army.erase(p->army.begin()+ arena[k]); //destroy the Personality
						p->arena.erase(p->arena.begin()+ k);
					}

					if(k == p->army.size()) break;
					k++;
				}
				//Print a message
				cout<< "Attacker's points - Defender's points < Province's defense"<< endl<<
					"Province is not destroyed!"<< endl<<
					"Attacker's points < Defender's points"<< endl<<
					"Defender loses followers or personalities from arena's army that attack>= points_attacker- points_defender"<< endl<<
					"Attacker loses all of the attacking Personalities and Followers"<< endl;
			}
		}
		cout<< "Surviving Personalities lose a point of honour"<< endl;
		//Surviving Personalities lose a point of honour
		for(int i= 0; i< arena.size(); i++){
			army[arena[i]]->decrement_honour();
			if(army[arena[i]]->get_honour() == 0){ //Perfom suicide
				army[arena[i]]->performSeppuku();
				army.erase(army.begin()+ arena[i]); //Destroy the Personality
			}
		}
		for(int i= 0; i< p->arena.size(); i++){
			p->army[arena[i]]->decrement_honour();
			if(p->army[arena[i]]->get_honour() == 0){ //Perfom suicide
				p->army[arena[i]]->performSeppuku();
				p->army.erase(p->army.begin()+ arena[i]); //Destroy the Personality
			}
		}
		cout<< "Print "<< this->name<< "'s Arena:"<< endl;
		printArena();
		cout<< "Print "<< p->name<< "'s Arena: "<< endl;
		p->printArena();
	}

}

void Player::printHoldings() const
{
	cout << "Printing holdings : " << endl << endl;
	for (vector<Holding*>::const_iterator it = holdings.begin(); it != holdings.end(); ++it)
	{
		(*it)->print();
	}

}

void Player::economyPhase()
{
	char input;
	unsigned int i;

	cout << "Player: " << this->name << " is playing " << endl;
	cout << "Economy Phase ..." << endl << endl;
	this->revealProvinces(); //reveal not-destroyed provinces
	cout << "Available money : " << money << endl << endl;
	this->printProvinces(); //prints not-destroyed provinces
	this->tapHoldings(); //tap any holdings in case you need extra money

	while(money)  //while player has money and wants to
	{
		input = '0';
		i = 0;
		cout << "Available money : " << money << endl << endl;
		while (input != 'y' && input != 'n')
		{
			cout << this->name<< ", do you want buy from any provinces (y:yes / n:no) ?" << endl;
			cin >> input;
		}

		if (input == 'n')
			return; //exit economy phase

		while (i < 1 || i > provinces.size())
		{
			this->printProvinces();
			cout << this->name<< ", choose a province to buy from : (1-" << provinces.size() << ")" << endl;
			cin >> i;
		}

		if (provinces[i-1]->is_revealed() == false)
		{
			cout <<"This province is not revealed yet, purchase cancelled" << endl;
			continue;
		}

		if (provinces[i-1]->get_cost() > money)
		{
			cout << "This province cannot be afforded, purchase cancelled" << endl;
			continue;
		}

		//at this point purchase is made
		money -= provinces[i-1]->get_cost();
		cout << "Province purchase successful " << endl << endl;
		this->equipProvince(provinces[i-1]); //add province to army or holdings vector and call checkChains for upper-sub holding connections
		//provinces.erase(provinces.begin() + (i-1)); //remove card from provinces
		provinces[i-1] = dynastyDeck->front(); //remove card from provinces and replace it with top of dynasty-deck (not revealed)
	    dynastyDeck->pop_front();
	}
}


void Player::tapHoldings()
{
	char input;
	unsigned int i, count = 0;

	while (holdings.size() -1 -count > 0) //while player possesses untapped holdings (other than stronghold)
	{
		input = '0';
		i=0;
		this->printHoldings(); //print players holdings so they can decide whether to tap a holding for extra money or not

		while (input != 'y' && input != 'n')
		{
			cout << this->name<< ", do you want to tap any of your holdings for extra money (y:yes / n:no) ?" << endl;
			cin >> input;
		}

		if (input == 'y')
		{
			while ( i < 1 || i > (holdings.size()-1))
			{
				this->printHoldings();
				cout << "Choose a holding to tap : (1-" << holdings.size() - 1 << ")" << endl;
				cin >> i;
			}

			if (holdings[i]->is_tapped() == true)
			{
				cout << "Card already tapped can't be used for the remainder of the round " << endl;
				continue;
			}

			holdings[i]->tap(); //card is tapped
			money += holdings[i]->get_harvestValue();
			count++;
			cout << "Holding tapped and its harvest value was added to your money " << endl << endl;
		}

		else
			return;

	}

}

void Player::equipProvince(BlackCard* card)
{
	Personality *person = NULL;
	Holding *hold = NULL;
	TypeConverter t;
	t.getCorrectType(card,&person,&hold);
	if (person == NULL) //if given black card is holding
	{
		this->checkChains(hold); //check for upper-sub holding connections
		holdings.push_back(hold); //push it to the vector of holdings of player
	}
	else
		army.push_back(person); //else push it to the army of player
}

void Player::checkChains(Holding* holding)
{
	cout << "Checking for possible chains ... " << endl << endl;

	Holding* upper = NULL;
	Holding* sub = NULL;
	if (holding->getHoldingType() == MINE) //if holding is mine you search for possible upper holding connections
	{
		for (unsigned int i = 1; i < holdings.size(); i++)  //you go through all players holdings other than stronghold obviously
		{
			if (holdings[i]->getHoldingType() == GOLD_MINE && upper == NULL && holdings[i]->hasSub() == false ) //chain goes mine --> gold mine
				upper = holdings[i];
			else if (holdings[i]->getHoldingType() == GOLD_MINE && upper != NULL &&
					holdings[i]->hasSub() == false && rand()%2 == 1) //if another gold mine is found choose in random
				upper = holdings[i];
		}

	}

	else if (holding->getHoldingType() == CRYSTAL_MINE) //if holding is crystal mine you search for possible sub holding connections
	{
		for (unsigned int i = 1; i < holdings.size(); i++)
		{
			if (holdings[i]->getHoldingType() == GOLD_MINE && sub == NULL && holdings[i]->hasUpper() == false) //chain goes crystal mine <-- gold mine
				sub = holdings[i];
			else if (holdings[i]->getHoldingType() == GOLD_MINE && sub != NULL &&
					holdings[i]->hasUpper() == false && rand()%2 == 1) //if another gold mine is found choose in random
				sub = holdings[i];
		}

	}

	else if (holding->getHoldingType() == GOLD_MINE) //if holding is gold mine you search for possible upper AND sub holding connections
	{
		for (unsigned int i = 1; i < holdings.size(); i++)
		{
			if (holdings[i]->getHoldingType() == MINE && sub == NULL && holdings[i]->hasUpper() == false) //chain goes gold mine <-- mine
				sub = holdings[i];
			else if (holdings[i]->getHoldingType() == MINE && sub != NULL &&
					holdings[i]->hasUpper() == false && rand()%2 == 1) //if another mine is found choose in random
				sub = holdings[i];

			if (holdings[i]->getHoldingType() == CRYSTAL_MINE && upper == NULL && holdings[i]->hasSub() == false) //chaing goes mine --> gold mine --> crystal mine
				upper = holdings[i];
			else if (holdings[i]->getHoldingType() == CRYSTAL_MINE && upper != NULL &&
					holdings[i]->hasSub() == false && rand()%2 == 1) //if another mine is found choose in random
				upper = holdings[i];
		}

	}

	if (upper != NULL) //if a possible upper holding connection is decided
		holding->setUpperHolding(upper);  //make connection
	if (sub != NULL) //if a possible sub holding connection is decided
		holding->setSubHolding(sub); //make connection

	if (upper != NULL || sub !=NULL) //if at least one connection was made
	{
		holding->equipBonus();  //update harvest value of holding with bonus
		cout << "Connections made , bonuses equipped " << endl << endl;
	}

	else
		cout << "No possible connections found :( " << endl << endl;
 //obviously if given holding is not mine or gold mine or crystal mine nothing happens and we just move on with our day


}

void Player::endingPhase()
{
	cout << "Player: " << this->name << " is playing " << endl;
	cout << "Ending Phase ..." << endl << endl;
	this->discardSurplusFateCards();
	this->printGameStatistics();
	this->printHand();
	this->printProvinces();
	this->printHoldings();
	this->printArena();
}

void Player::discardSurplusFateCards()
{
	unsigned int card;

	if (hand.size() > NO_HAND)
	{
		cout << "You have surplus fate cards in your hand (max " << NO_HAND << " and you have " << hand.size() << " )" << endl;
		cout << "You need to discard " << hand.size() - NO_HAND << " cards from your hand ..." << endl;
		for (unsigned int i = 0; i < hand.size() - NO_HAND; i++)
		{
			card = 0;
			while (card < 1 || card > hand.size())
			{
				this->printHand();
				cout << this->name<< ", choose a card from your hand to discard : (1-" << hand.size() << ")" << endl;
				cin >> card;
			}

			hand.erase(hand.begin() + (card-1)); //erase card from hand
		}
	}

	cout << "Surplus fate cards discarded! " << endl << endl;

}

void Player::printArena() const{
	cout<< "Printing Arena : "<< endl<< endl;
	for(int i= 0; i< arena.size(); i++)
		army[arena[i]]->print();
}
