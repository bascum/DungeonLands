#include <string>
#include "Inventory.h"
#include "Item.h"
#include "Die.h"
#include "WeightedDie.h"

Trait::Trait(std::string n, std::string d, int r)
{
	name = n;
	traitDescription = d;
	req = r;
}

Item::Item(std::string n, int d, int r)
{
	type = n;
	dmgDie = d;
	rarity = r;
}

Item::Item(std::string n, int d, Trait* t)
{
	type = n;
	dmgDie = d;
	rarity = t->req;
	itemTrait = t;
}

std::string Item::getType()
{
	return type;
}

int Item::getDmgDie()
{
	return dmgDie;
}
