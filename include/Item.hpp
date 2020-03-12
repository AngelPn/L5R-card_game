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

	int getType() const
	{
		return ITEM;
	}

	unsigned int get_durability() const { return durability; }

	void decrement_durability(){ durability--; }

	virtual void print() const{
		std::cout<< "\033[1;32mCost: \033[0m"<< cost<< "\033[1;32m\nAttack Bonus: \033[0m"<< attackBonus<<
		 "\033[1;32m\nDefense Bonus: \033[0m"<< defenseBonus<< "\033[1;32m\nMinimum Honor: \033[0m"<< minimumHonor
			<< "\033[1;32m\nEffect Bonus: \033[0m"<< effectBonus<< "\033[1;32m\nEffect Cost: \033[0m"<< effectCost<<
			"\033[1;32m\nDurability: \033[0m"<< durability<< "\n";
		GreenCard::print();
	}
};

class Katana : public Item {

public:
	Katana(const std::string name, int type) : Item(name, type){}

	void print() const{
		std::cout<< "\033[1;32mItem: KATANA\n\033[0m";
		Item::print();
	}
};

class Spear : public Item {

public:
	Spear(const std::string name, int type) : Item(name, type){}

	void print() const{
		std::cout<< "\033[1;32mItem: SPEAR\n\033[0m";
		Item::print();
	}
};

class Bow : public Item {

public:
	Bow(const std::string name, int type) : Item(name, type){}

	void print() const{
		std::cout<< "\033[1;32mItem: BOW\n\033[0m";
		Item::print();
	}
};

class Ninjato : public Item {

public:
	Ninjato(const std::string name, int type) : Item(name, type){}

	void print() const{
		std::cout<< "\033[1;32mItem: NINJATO\n\033[0m";
		Item::print();
	}
};

class Wakizashi : public Item {

public:
	Wakizashi(const std::string name, int type) : Item(name, type){}

	void print() const{
		std::cout<< "\033[1;32mItem: WAKIZASHI\n\033[0m";
		Item::print();
	}
};

#endif
