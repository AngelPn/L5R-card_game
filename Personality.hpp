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
	Personality(const std::string name, int type) : BlackCard(name, type), isDead(0);
	~Personality();

  int getType() const;

	//Accessors
	bool is_dead() const;
	unsigned int get_attack() const;
	unsigned int get_defense() const;
	unsigned int get_honour() const;

	virtual void print() const;
	bool hasFollowers();
	void destroyFollower(int *lost_points);
	void tap_followers();
	void decrement_durability();
	void decrement_honour();
	void performSeppuku();
	bool belowBound() const;
	void applyBonus(GreenCard *card);
	void equip(GreenCard *card);
};

class Attacker : public Personality {

public:
	Attacker(const std::string name, int type) : Personality(name, type){}

	void print() const{
		std::cout<< "\033[1;31mPersonality: ATTACKER\n\033[0m";
		Personality::print();
	}
};

class Defender : public Personality {

public:
	Defender(const std::string name, int type) : Personality(name, type){}

	void print() const{
		std::cout<< "\033[1;31mPersonality: DEFENDER\n\033[0m";
		Personality::print();
	}
};

class Champion : public Personality {

public:
	Champion(const std::string name, int type) : Personality(name, type){}

	void print() const{
		std::cout<< "\033[1;31mPersonality: CHAMPION\n\033[0m";
		Personality::print();
	}
};

class Chancellor : public Personality {

public:
	Chancellor(const std::string name, int type) : Personality(name, type){}

	void print() const{
		std::cout<< "\033[1;31mPersonality: CHANCELLOR\n\033[0m";
		Personality::print();
	}
};

class Shogun : public Personality {

public:
	Shogun(const std::string name, int type) : Personality(name, type){}

	void print() const{
		std::cout<< "\033[1;31mPersonality: SHOGUN\n\033[0m";
		Personality::print();
	}
};

#endif
