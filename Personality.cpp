//file:Personality.cpp
#include "Personality.hpp"
#include "TypeConverter.hpp"

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
