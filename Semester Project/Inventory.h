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

private:
	Node* head = NULL;
	int invSize = 0;
	std::vector<Item*> itemTypeList;
	std::vector<Trait*> traitList;

	void loadItemTypes();
	void loadTraits();
};

#endif