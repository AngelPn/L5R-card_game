//file:Card.hpp
#ifndef _CARD_HPP_
#define _CARD_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

enum Personalities{ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
enum Holdings{PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};
enum Followers{FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO };
enum Items{KATANA, SPEAR, BOW, NINJATO, WAKIZASHI };
enum Types{PERSONALITY = 1, HOLDING, FOLLOWER, ITEM};

class Card{
private:
	std::string name;

protected:
	unsigned int cost; //cost is protected in order to be initialized from sub-class constructor
	bool isTapped; //untapped= 0, tapped=1

public:
	Card(std::string name_): name(name_), isTapped(0){ }

	//Card(const Card& c): name(c.name), isTapped(c.isTapped), cost(c.cost){ } //Copy constructor

	std::string get_name() const{ return name; }
	bool is_tapped() const{ return isTapped; }
	unsigned int get_cost() const { return this->cost; }

    //getType is a function that needs to exist in all sub-classes of Card but with different implementation
    //in each subclass, also no objects of Card need to be created so we make it abstract (pure virtual)
	virtual int getType() const = 0;
  virtual void print() const = 0; //for the same reasons , the print card function is pure virtual
  void untap() { isTapped = 0; }  //untaps card
	void tap() { isTapped = 1; } //taps card

};

namespace {int no_cardTextes= 12;} //Set the number of card textes that file "CardTextes.txt" has

class GreenCard: public Card{
private:
	std::string cardText;
protected:
	unsigned int attackBonus;  //all these are protected in order to be initialized from sub-class constructor
	unsigned int defenseBonus;
	unsigned int minimumHonor;
	unsigned int effectBonus;
	unsigned int effectCost;

public:
	GreenCard(std::string name, int type): Card(name){
  		std::ifstream file("CardTextes.txt"); //Open file and read it

  		if(!no_cardTextes){ //In case all card textes are used
  			no_cardTextes= 12; //Reset the number of card textes
  		}
  		int i= no_cardTextes;
  		while(i){ //Get a unique card text each time a GreenCard is created
  			getline(file, this->cardText);
  			i--;
  		}
  		no_cardTextes--;
  		file.close(); //Close the file
	}

	//GreenCard(const GreenCard &gc): Card(gc) //Copy constructor: specify base initialization in the initialization list
	//{
		//this->attackBonus= gc.attackBonus;
		//this->defenseBonus= gc.defenseBonus;
		//this->minimumHonor= gc.minimumHonor;
		//this->effectBonus= gc.effectBonus;
		//this->effectCost= gc.effectCost;
		//this->cardText= gc.cardText;
	//}

	virtual void print() const{
		std::cout<< "Card Text: "<< cardText<< std::endl<< "Name: "<< Card::get_name()<< std::endl << std::endl;
	}

	unsigned int get_honour() const { return this->minimumHonor; }
	unsigned int get_effectCost() const {return this->effectCost; }
	unsigned int get_attackBonus() const {return this->attackBonus; }
	unsigned int get_defenseBonus() const {return this->defenseBonus; }

	void applyBonus(){
		attackBonus += effectBonus;
		defenseBonus += effectBonus;
	}
};

class BlackCard: public Card{
private:
	bool isRevealed; //0 not releaved, 1 releaved

public:
	BlackCard(std::string name, int type): Card(name), isRevealed(0){}
	virtual ~BlackCard(){}
	//BlackCard(const BlackCard& bc): Card(bc), isRevealed(bc.isRevealed){ } //Copy constructor

	bool is_revealed() const { return isRevealed; }
	void reveal() { isRevealed = 1; }
	virtual void print() const{
		std::cout<< "Name: "<< Card::get_name()<< std::endl << std::endl;
	}
};

#endif
