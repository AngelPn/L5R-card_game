//file:Personality.cpp
#include "Personality.hpp"
#include "TypeConverter.hpp"

Personality::Personality(const std::string name, int type) : BlackCard(name, type), isDead(0)
//constructors of BlackCard and Card will initialize the data members which are not in the .txt files
//data members with values from the .txt file, are initialized here
{
	switch (type)
	{
		case ATTACKER   : cost= 5; attack = 3; defense = 2; honour = 2; greenCardBound = 3; break;
		case DEFENDER   : cost= 5; attack = 2; defense = 3; honour = 2; greenCardBound = 3; break;
		case SHOGUN     : cost= 15; attack = 10; defense = 5; honour = 8; greenCardBound = 4; break;
		case CHANCELLOR : cost= 15; attack = 5; defense = 10; honour = 8; greenCardBound = 4; break;
		case CHAMPION   : cost= 30; attack = 20; defense = 20; honour = 12; greenCardBound = 5; break;
	}

	followers = new std::list<Follower*>();
	items = new std::list<Item*>();
}

Personality::~Personality()
{
	items->clear();
	delete items;
	followers->clear();
	delete followers;
}

int Personality::getType() const { return PERSONALITY; }

//Accessors
bool Personality::is_dead() const { return isDead; }
unsigned int Personality::get_attack() const { return attack; }
unsigned int Personality::get_defense() const { return defense; }
unsigned int Personality::get_honour() const { return honour; }

bool Personality::hasFollowers(){
	if(followers->empty()) return true;
	else return false;
}

void Personality::destroyFollower(int *lost_points){
	(*lost_points)+= followers->front()->get_attackBonus();
	followers->pop_front();
}

void Personality::tap_followers(){
	std::list<Follower *>::iterator it;
	for (it = followers->begin(); it != followers->end(); it++)
		(*it)->tap();
}

void Personality::decrement_durability(){
	std::list<Item *>::iterator it;
	for (it = items->begin(); it != items->end(); it++){
		(*it)->decrement_durability();
		if((*it)->get_durability() == 0)
			items->erase(it);
	}
}

void Personality::decrement_honour(){
	honour--;
}

void Personality::performSeppuku(){
	std::cout<< "I am going to perform Seppuku"<< std::endl;
}

bool Personality::belowBound() const  //returns true if green card bound is not exceeded for this personality, otherwise returns false
{
	if (greenCardBound > followers->size() + items->size())  //folowers size + items size is total green cards possessed
		return true;
	else
		return false;
}

void Personality::print() const{
	std::cout<< "\033[1;31mCost: \033[0m"<< cost<< "\033[1;31m\nAttack: \033[0m"<< attack<< "\033[1;31m\nDefense: \033[0m"<< defense<<
	"\033[1;31m\nHonour: \033[0m"<< honour<< "\033[1;31m\nGreen cards attached : \033[0m"
	<< followers->size() + items->size() << "\033[1;31m\nMax green cards :\033[0m" << greenCardBound << std::endl;
	BlackCard::print();
}

void Personality::applyBonus(GreenCard *card)
{
	this->attack += card->get_attackBonus();
	this->defense += card->get_defenseBonus();
}

void Personality::equip(GreenCard *card)
{
	Follower *follow = NULL;
	Item *item = NULL;
	TypeConverter t;
	t.getCorrectType(card,&follow,&item);
	if (follow == NULL) //if given green card is item
		items->push_back(item); //push it to the vector of items of personality
	else
		followers->push_back(follow); //else push it to the vector of followers of personality
}
