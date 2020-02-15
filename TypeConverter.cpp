#include "TypeConverter.hpp"

TypeConverter::TypeConverter() {}

void TypeConverter::getCorrectType(BlackCard *card, Personality **person, Holding **hold)
{
	if (card->getType() == PERSONALITY) {
		(*person) = getPersonality(card);
		(*hold) = NULL;
	}
	else {
		(*hold) = getHolding(card);
		(*person) = NULL;
	}
}

void TypeConverter::getCorrectType(GreenCard *card, Follower **follow, Item **item)
{
	if (card->getType() == FOLLOWER) {
		(*follow) = getFollower(card);
		(*item) = NULL;
	}
	else {
		(*item) = getItem(card);
		(*follow) = NULL;
	}
}

Personality *TypeConverter::getPersonality(BlackCard *d)
{
	if (d->getType() == PERSONALITY)
		return dynamic_cast<Personality *>(d);
	return NULL;
}

Holding *TypeConverter::getHolding(BlackCard *d)
{
	if (d->getType() == HOLDING)
		return dynamic_cast<Holding *>(d);
	return NULL;
}

Follower *TypeConverter::getFollower(GreenCard *d)
{
	if (d->getType() == FOLLOWER)
		return dynamic_cast<Follower *>(d);
	return NULL;
}

Item *TypeConverter::getItem(GreenCard *d)
{
	if (d->getType() == ITEM)
		return dynamic_cast<Item *>(d);
	return NULL;
}