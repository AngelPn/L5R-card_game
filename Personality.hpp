//file:Personality.hpp
#ifndef _PERSONALITY_HPP_
#define _PERSONALITY_HPP_
#include "Card.hpp"
#include <string>
#include <list>

#include "Follower.hpp"
#include "Item.hpp"

class Personality : public BlackCard {

private:
	bool isDead; //0 alive, 1 dead
	unsigned int attack;
	unsigned int defense;
	unsigned int honour;
	std::list<Follower*> *followers;
	std::list<Item*> *items;
	unsigned int greenCardBound;

public: //int type-> Personalities type
	Personality(const std::string name, int type) : BlackCard(name, type), isDead(0)
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

	~Personality()
	{
		items->clear();
		delete items;
		followers->clear();
		delete followers;
	}

	//Personality(const Personality &p): BlackCard(p), isDead(p.isDead), attack(p.attack), defense(p.defense), honour(p.honour){
	//	for(int i=0; i< p.followers.size(); i++)
	//		this->followers.push_back(p.followers[i]);
	//	for(int i=0; i< p.items.size(); i++)
	//		this->items.push_back(p.items[i]);
	//}

	//accessors that will probably be needed , NOTE: Will probably be changed or enhanced later

    int getType() const
	{
		return PERSONALITY;
	}
	//Accessors
	bool is_dead() const { return isDead; }
	unsigned int get_attack() const { return attack; }
	unsigned int get_defense() const { return defense; }
	unsigned int get_honour() const { return honour; }

	bool hasFollowers(){
		if(followers->empty()) return true;
		else return false;
	}

	void destroyFollower(int *lost_points){
		(*lost_points)+= followers->front()->get_attackBonus();
		followers->pop_front();
	}

	void tap_followers(){
		std::list<Follower *>::iterator it;
		for (it = followers->begin(); it != followers->end(); it++)
			(*it)->tap();
	}

	void decrement_durability(){
		std::list<Item *>::iterator it;
		for (it = items->begin(); it != items->end(); it++){
			(*it)->decrement_durability();
			if((*it)->get_durability() == 0)
				items->erase(it);
		}
	}

	void decrement_honour(){
		honour--;
	}

	void performSeppuku(){
		std::cout<< "I am going to perform Seppuku"<< std::endl;
	}

	bool belowBound() const  //returns true if green card bound is not exceeded for this personality, otherwise returns false
	{
		if (greenCardBound > followers->size() + items->size())  //folowers size + items size is total green cards possessed
			return true;
		else
			return false;
	}

	virtual void print() const{
		std::cout<< "Cost: "<< cost<< "\nAttack: "<< attack<< "\nDefense: "<< defense<< "\nHonour: "<< honour<< "\nGreen cards attached : "
		<< followers->size() + items->size() << "\nMax green cards :" << greenCardBound << std::endl;
		BlackCard::print();
	}

	void applyBonus(GreenCard *card)
	{
		this->attack += card->get_attackBonus();
		this->defense += card->get_defenseBonus();
	}

	void equip(GreenCard *card);
};

class Attacker : public Personality {

public:
	Attacker(const std::string name, int type) : Personality(name, type){}

	//Attacker(const Attacker &a): Personality(a){ }

	void print() const{
		std::cout<< "Personality: ATTACKER\n";
		Personality::print();
	}
};

class Defender : public Personality {

public:
	Defender(const std::string name, int type) : Personality(name, type){}

	//Defender(const Defender &a): Personality(a){ }

	void print() const{
		std::cout<< "Personality: DEFENDER\n";
		Personality::print();
	}
};

class Champion : public Personality {

public:
	Champion(const std::string name, int type) : Personality(name, type){}

	//Champion(const Champion &a): Personality(a){ }

	void print() const{
		std::cout<< "Personality: CHAMPION\n";
		Personality::print();
	}
};

class Chancellor : public Personality {

public:
	Chancellor(const std::string name, int type) : Personality(name, type){}

	//Chancellor(const Chancellor &a): Personality(a){ }

	void print() const{
		std::cout<< "Personality: CHANCELLOR\n";
		Personality::print();
	}
};

class Shogun : public Personality {

public:
	Shogun(const std::string name, int type) : Personality(name, type){}

	//Shogun(const Shogun &a): Personality(a){ }

	void print() const{
		std::cout<< "Personality: SHOGUN\n";
		Personality::print();
	}
};

#endif
