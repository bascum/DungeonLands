#include <string>
#include <vector>
#include "Item.h"

#ifndef INVENTORY_H
#define INVENTORY_H


struct Node//Basic node with data and a next keyword.
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
	Inventory(); //Constructor

	void addRandItem(); // generates a random item
	void addItem(std::string, int); // generates a custom item which takes input from the user

	void displayInv(); // Displays a list of all the items currently in the list

	void delItem(); //Deletes and item

private:
	Node* head = NULL;
	Node* sorted = NULL;
	int invSize = 0;
	std::vector<Item*> itemTypeList;
	std::vector<Trait*> traitList;

	void delNode(int);
	Node* findNode(int);

	Trait* getRandTrait(int);

	void loadItemTypes();
	void loadTraits();

	void showTraitList();
	void insertionSort();
	void sort(Node*);
};

#endif