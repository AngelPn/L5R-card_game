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

	//Follower(const Follower &f): GreenCard(f){ } //Copy constructor: specify base initialization in the initialization list

	int getType() const
	/*getType function returns an integer based on the category of the card based on the enumeration {PERSONALITY = 1, HOLDING, FOLLOWER, ITEM}*/
	{
		return FOLLOWER; 
	}

	virtual void print() const{
		std::cout<< "Cost: "<< cost<< "\nAttack Bonus: "<< attackBonus<< "\nDefense Bonus: "<< defenseBonus<< "\nMinimum Honor: "<< minimumHonor
			<< "\nEffect Bonus: "<< effectBonus<< "\nEffect Cost: "<< effectCost<< "\n";
		GreenCard::print();
	}
};

class Footsoldier : public Follower {

public:
	Footsoldier(const std::string name, int type) : Follower(name, type){}

	//Footsoldier(const Footsoldier &f): Follower(f){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: FOOTSOLDIER\n";
		Follower::print(); //Call base class function
	}
};

class Archer : public Follower {

public:
	Archer(const std::string name, int type) : Follower(name, type){}

	//Archer(const Archer &a): Follower(a){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: ARCHER\n";
		Follower::print(); //Call base class function
	}
};

class Cavalry : public Follower {

public:
	Cavalry(const std::string name, int type) : Follower(name, type){}

	//Cavalry(const Cavalry &c): Follower(c){ }//Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: CAVALRY\n";
		Follower::print(); //Call base class function
	}
};

class Bushido : public Follower {

public:
	Bushido(const std::string name, int type) : Follower(name, type){}

	//Bushido(const Bushido &b): Follower(b){ }//Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: BUSHIDO\n";
		Follower::print(); //Call base class function
	}
};

class Sieger : public Follower {

public:
	Sieger(const std::string name, int type) : Follower(name, type){}

	//Sieger(const Sieger &s): Follower(s){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: SIEGER\n";
		Follower::print(); //Call base class function
	}
};

class Atakebune : public Follower {

public:
	Atakebune(const std::string name, int type) : Follower(name, type){}

	//Atakebune(const Atakebune &a): Follower(a){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Follower: ATAKEBUNE\n";
		Follower::print(); //Call base class function
	}
};

#endif
