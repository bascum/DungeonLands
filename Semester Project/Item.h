#include <string>

#ifndef ITEM_H
#define ITEM_H

struct Trait
{
public:
	Trait(std::string, std::string, int);

	std::string name;
	std::string traitDescription;
	int req; //short for requirement
};

class Item
{
private:

	bool hasData = false;
	std::string type;


	int dmgDie = 0;
	int rarity = 0; //Weighted Die roll 1-20 / 4 to get range 0 - 4

	Trait* itemTrait = NULL;

public:
	Item(std::string, int, int = 0);
	Item(std::string, int, Trait*);
	Item() = default;

	std::string getType();

	int getDmgDie();
};

#endif