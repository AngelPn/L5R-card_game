//file:Follower.hpp
#ifndef _FOLLOWER_HPP_
#define _FOLLOWER_HPP_
#include "Card.hpp"
#include <string>

class Follower: public GreenCard {

public:
	Follower(const std::string name, int type): GreenCard(name, type)
	//constructors of GreenCard and Card will initialize the data members which are not in the .txt files
	//data members with values from the .txt file, are initialized here
	{
		switch (type)
		{
			case FOOTSOLDIER : cost= 0; attackBonus = 2; defenseBonus = 0; minimumHonor = 1; effectBonus = 1; effectCost = 2; break;
			case ARCHER      : cost= 0; attackBonus = 0; defenseBonus = 2; minimumHonor = 1; effectBonus = 1; effectCost = 2; break;
			case SIEGER      : cost= 5; attackBonus = 3; defenseBonus = 3; minimumHonor = 2; effectBonus = 2; effectCost = 3; break;
			case CAVALRY     : cost= 3; attackBonus = 4; defenseBonus = 2; minimumHonor = 3; effectBonus = 3; effectCost = 4; break;
			case NAVAL       : cost= 3; attackBonus = 2; defenseBonus = 4; minimumHonor = 3; effectBonus = 3; effectCost = 4; break;
			case BUSHIDO     : cost= 8; attackBonus = 8; defenseBonus = 8; minimumHonor = 6; effectBonus = 3; effectCost = 8; break;
		}

	}

	int getType() const
	/*getType function returns an integer based on the category of the card based on the enumeration {PERSONALITY = 1, HOLDING, FOLLOWER, ITEM}*/
	{
		return FOLLOWER;
	}

	virtual void print() const{
		std::cout<< "\033[1;32mCost: \033[0m"<< cost<< "\033[1;32m\nAttack Bonus: \033[0m"<< attackBonus<<
		"\033[1;32m\nDefense Bonus: \033[0m"<< defenseBonus<< "\033[1;32m\nMinimum Honor: \033[0m"<< minimumHonor
			<< "\033[1;32m\nEffect Bonus: \033[0m"<< effectBonus<< "\033[1;32m\nEffect Cost: \033[0m"<< effectCost<< "\n";
		GreenCard::print();
	}
};

class Footsoldier : public Follower {

public:
	Footsoldier(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: FOOTSOLDIER\n\033[0m";
		Follower::print(); //Call base class function
	}
};

class Archer : public Follower {

public:
	Archer(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: ARCHER\n\033[0m";
		Follower::print(); //Call base class function
	}
};

class Cavalry : public Follower {

public:
	Cavalry(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: CAVALRY\n\033[0m";
		Follower::print(); //Call base class function
	}
};

class Bushido : public Follower {

public:
	Bushido(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: BUSHIDO\n\033[0m";
		Follower::print(); //Call base class function
	}
};

class Sieger : public Follower {

public:
	Sieger(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: SIEGER\n\033[0m";
		Follower::print(); //Call base class function
	}
};

class Atakebune : public Follower {

public:
	Atakebune(const std::string name, int type) : Follower(name, type){}

	void print() const{
		std::cout<< "\033[1;32mFollower: ATAKEBUNE\n\033[0m";
		Follower::print(); //Call base class function
	}
};

#endif
