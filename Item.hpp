//file:Item.hpp
#ifndef _ITEM_HPP_
#define _ITEM_HPP_
#include "Card.hpp"
#include <string>

class Item : public GreenCard {

private:
	unsigned int durability;

public:
	Item(const std::string name, int type) : GreenCard(name, type)
	//constructors of GreenCard and Card will initialize the data members which are not in the .txt files
	//data members with values from the .txt file, are initialized here
	{
		switch (type)
		{
			case KATANA    : cost= 0; attackBonus = 2; defenseBonus = 0; minimumHonor = 1; effectBonus= 1; effectCost= 2; durability = 3; break;
			case SPEAR     : cost= 0; attackBonus = 0; defenseBonus = 2; minimumHonor = 1; effectBonus= 1; effectCost= 2; durability = 3; break;
			case BOW       : cost= 2; attackBonus = 2; defenseBonus = 2; minimumHonor = 2; effectBonus= 3; effectCost= 4; durability = 5; break;
			case NINJATO   : cost= 4; attackBonus = 3; defenseBonus = 3; minimumHonor = 3; effectBonus= 2; effectCost= 2; durability = 4; break;
			case WAKIZASHI : cost= 8; attackBonus = 5; defenseBonus = 5; minimumHonor = 3; effectBonus= 3; effectCost= 3; durability = 8; break;
		}
	}

	//Item(const Item &i): GreenCard(i), durability(i.durability){ } //Copy constructor: specify base initialization in the initialization list

	int getType() const
	{
		return ITEM;
	}

	unsigned int get_durability() const
	{
		return durability;
	}

	void decrement_durability(){
		durability--;
	}

	virtual void print() const{
		std::cout<< "Cost: "<< cost<< "\nAttack Bonus: "<< attackBonus<< "\nDefense Bonus: "<< defenseBonus<< "\nMinimum Honor: "<< minimumHonor
			<< "\nEffect Bonus: "<< effectBonus<< "\nEffect Cost: "<< effectCost<< "\nDurability: "<< durability<< "\n";
		GreenCard::print();
	}
};

class Katana : public Item {

public:
	Katana(const std::string name, int type) : Item(name, type){}

	//Katana(const Katana &k): Item(k){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Item: KATANA\n";
		Item::print();
	}
};

class Spear : public Item {

public:
	Spear(const std::string name, int type) : Item(name, type){}

	//Spear(const Spear &k): Item(k){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Item: SPEAR\n";
		Item::print();
	}
};

class Bow : public Item {

public:
	Bow(const std::string name, int type) : Item(name, type){}

	//Bow(const Bow &k): Item(k){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Item: BOW\n";
		Item::print();
	}
};

class Ninjato : public Item {

public:
	Ninjato(const std::string name, int type) : Item(name, type){}

	//Ninjato(const Ninjato &k): Item(k){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Item: NINJATO\n";
		Item::print();
	}
};

class Wakizashi : public Item {

public:
	Wakizashi(const std::string name, int type) : Item(name, type){}

	//Wakizashi(const Wakizashi &k): Item(k){ } //Copy constructor: specify base initialization in the initialization list

	void print() const{
		std::cout<< "Item: WAKIZASHI\n";
		Item::print();
	}
};

#endif
