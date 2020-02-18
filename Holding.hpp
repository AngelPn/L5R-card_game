//file:Holding.hpp
#ifndef _HOLDING_HPP_
#define _HOLDING_HPP_
#include "Card.hpp"
#include <string>

class Holding : public BlackCard {

private:
  Holding *upperHolding;
	Holding *subHolding;
	unsigned int harvestValue;

public:
	Holding(const std::string name, int type) : BlackCard(name, type), upperHolding(NULL), subHolding(NULL)
	//constructors of BlackCard and Card will initialize the data members which are not in the .txt files
	//data members with values from the .txt file, are initialized here
	{
		switch (type)
		{
			case PLAIN        : cost= 2; harvestValue = 2; break;
			case SOLO         : cost= 2; harvestValue = 2; break;
			case MINE         : cost= 5; harvestValue = 3; break;
			case FARMS        : cost= 3; harvestValue = 4; break;
			case GOLD_MINE    : cost= 7; harvestValue = 5; break;
			case STRONGHOLD   : cost= 0; harvestValue = 5; break;
			case CRYSTAL_MINE : cost= 12; harvestValue = 6; break;
		}
	}

	unsigned int get_harvestValue() const{ return harvestValue; }

  virtual unsigned int initialMoney() const {}

	int getType() const
	{
		return HOLDING;
	}

  virtual int getHoldingType() const {}
  virtual unsigned int get_initialDefense() const {}

	void setUpperHolding(Holding* holding) {upperHolding = holding;}
	void setSubHolding(Holding* holding)  {subHolding = holding;}

	bool hasUpper() const { return (upperHolding!=NULL) ? true : false; }
	bool hasSub() const { return (subHolding!=NULL) ? true : false; }

	void equipBonus() //updates harvest value with bonus from upper,sub connections
	{
		if (this->getHoldingType() == MINE && upperHolding != NULL)
			this->harvestValue += 2;
		else if (this->getHoldingType() == GOLD_MINE && subHolding != NULL && upperHolding == NULL)
			this->harvestValue += 4;
		else if (this->getHoldingType() == GOLD_MINE && subHolding == NULL && upperHolding != NULL)
			this->harvestValue += 5;
		else if (this->getHoldingType() == GOLD_MINE && subHolding != NULL && upperHolding != NULL)
			this->harvestValue *= 2;
		else if (this->getHoldingType() == CRYSTAL_MINE && subHolding != NULL && subHolding->subHolding == NULL)
			this->harvestValue *= 2;
		else if (this->getHoldingType() == CRYSTAL_MINE && subHolding != NULL && subHolding->subHolding != NULL)
			this->harvestValue *= 3;
	}

	virtual void print() const{
		std::cout<< "\033[1;31mCost: \033[0m"<< cost<< "\033[1;31m\nHarvest Value: \033[0m"<< harvestValue<< "\n";
		BlackCard::print();
	}
};

class Plain : public Holding {

public:
	Plain(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return PLAIN;}

	void print() const{
		std::cout<< "\033[1;31mHolding: PLAIN\n\033[0m";
		Holding::print();
	}
};

class Mine : public Holding {

public:
	Mine(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return MINE;}

	void print() const{
		std::cout<< "\033[1;31mHolding: MINE\n\033[0m";
		Holding::print();
	}
};

class GoldMine : public Holding {

public:
	GoldMine(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return GOLD_MINE;}

	void print() const{
		std::cout<< "\033[1;31mHolding: GOLD_MINE\n\033[0m";
		Holding::print();
	}
};

class CrystalMine : public Holding {

public:
	CrystalMine(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return CRYSTAL_MINE;}

	void print() const{
		std::cout<< "\033[1;31mHolding: CRYSTAL_MINE\n\033[0m";
		Holding::print();
	}
};

class Farmland : public Holding {

public:
	Farmland(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return FARMS;}

	void print() const{
		std::cout<< "\033[1;31mHolding: FARMLAND\n\033[0m";
		Holding::print();
	}
};

class GiftsandFavour : public Holding {

public:
	GiftsandFavour(const std::string name, int type) : Holding(name, type){}

  int getHoldingType() const { return SOLO; }

	void print() const{
		std::cout<< "\033[1;31mHolding: GIFTS and FAVOUR\n\033[0m";
		Holding::print();
	}
};

class Stronghold : public Holding {

private:
	//Stronghold's members have standarized values which are used as starting values for each player
	//thus we have declared them as const
	const unsigned int honour;
	const unsigned int money ;
	const unsigned int initialDefense;

public:
	Stronghold() : Holding("Stronghold", STRONGHOLD), honour(5), money(10), initialDefense(5){}

	unsigned int get_initialDefense() const { return initialDefense; }
  unsigned int initialMoney() const { return this->money; }
  int getHoldingType() const { return STRONGHOLD; }

	void print() const{
		std::cout<< "\033[1;31mHolding: STRONGHOLD\n\033[0m";
		Holding::print();
	}
};

#endif
