#include <string>
#include "Item.h"


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

std::string Item::getType()
{
	return type;
}

void Item::setType()
{

}

int Item::getDmgDie()
{
	return dmgDie;
}