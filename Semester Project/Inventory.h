#include <string>
#include <vector>
#include "Item.h"

#ifndef INVENTORY_H
#define INVENTORY_H


struct Node
{
	Node(Item b, Node* next = NULL)
	{
		data = b;
		next = next;
	}
	Item data;
	Node* next = NULL;
};

class Inventory
{
public:
	Inventory();

	void addRandItem();
	void addItem(std::string, int);

	void displayInv();

	void delItem();

private:
	Node* head = NULL;
	int invSize = 0;
	std::vector<Item*> itemTypeList;
	std::vector<Trait*> traitList;

	void delNode(int);
	Node* findNode(int);

	Trait* getRandTrait(int);

	void loadItemTypes();
	void loadTraits();

	void showTraitList();
};

#endif