#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Inventory.h"
#include "WeightedDie.h"
#include "Item.h"

Inventory::Inventory()
{
	loadItemTypes();
	loadTraits();
}

void Inventory::addItem(std::string t, int d)
{
	char chChoice;
	int intChoice = 0;
	std::cout << "\nWill the Item have a trait? (Y/N): ";
	std::cin >> chChoice;

	Item* tPtr = NULL;

	if (chChoice == 'Y' || chChoice == 'y')
	{
		std::cout << "\n\n*** Please select a trait from the list below ***\n";
		showTraitList();
		std::cin >> intChoice;

		tPtr = new Item(t, d, traitList[intChoice - 1]);
	}
	else
	{
		tPtr = new Item(t, d);
	}

	Node* newItem = new Node(*tPtr);

	if (head == NULL)
	{
		head = newItem;
	}
	else if (head != NULL)
	{
		newItem->next = head;
		head = newItem;
	}
}

void Inventory::addRandItem() 
{
	char userChoice = NULL;
	std::cout << "\n***Is this a Normal Item or a Special Item? (N/S): ";
	std::cin.ignore();
	std::cin.clear();
	std::cin >> userChoice;

	if (userChoice == 'N' || userChoice == 'n')
	{
		Die tempD20(20);
		int roll = tempD20.roll() - 1;
		Item tempItem(itemTypeList[roll]->getType(), itemTypeList[roll]->getDmgDie());
		
		Node* newItem = new Node(tempItem);

		if (head == NULL)
		{
			head = newItem;
		}
		else if (head != NULL)
		{
			newItem->next = head;
			head = newItem;
		}
	}
	else if (userChoice == 'S' || userChoice == 's')
	{
		Die d20(20);
		WeightedDie wD20(20);
		int unweightedRoll = d20.roll() - 1;
		Item tempItem(itemTypeList[unweightedRoll]->getType(), itemTypeList[unweightedRoll]->getDmgDie(), wD20.genRoll() + 1);

		Node* newItem = new Node(tempItem);

		if (head == NULL)
		{
			head = newItem;
		}
		else if (head != NULL)
		{
			newItem->next = head;
			head = newItem;
		}
	}
}

void Inventory::displayInv()
{
	Node* tempHead = head;
	int count = 1;
	do {
		std::cout << "\n" << count << ") NAME: " << tempHead->data.getType() << "\n   DMG : " << tempHead->data.getDmgDie();
		if (tempHead->next != NULL)
		{
			tempHead = tempHead->next;
		}
	} while (tempHead->next != NULL);
}

void Inventory::showTraitList()
{
	for (int i = 0; i < traitList.size(); i++)
	{
		std::cout << i + 1 << ") " << traitList[i]->name << " : Required Rarity (" << traitList[i]->req << "\n----(" << traitList[i]->traitDescription << std::endl;
	}
}

/*
Trait Inventory::findTrait(int i)
{
	if (i < traitList.size())
	{
		return *traitList[i];
	}
	else
	{
		throw "Error Out of Bounds";
	}
}

Item Inventory::findItem(int i)
{
	if (i < itemTypeList.size())
	{
		return *itemTypeList[i];
	}
	else
	{
		throw "Error Out of Bounds";
	}
}*/

void Inventory::loadItemTypes()
{
	itemTypeList.clear();

	std::string tempT;
	std::string stringToInt;

	Item* tempItem = NULL;

	int tempInt;

	std::string fileName = "Melee_Items.txt";
	std::ifstream FILE(fileName);

	while (!FILE.eof())
	{
		std::stringstream converter;

		getline(FILE, tempT, '/');

		getline(FILE, stringToInt);

		converter << stringToInt;
		converter >> tempInt;

		tempItem = new Item(tempT, tempInt);
		itemTypeList.push_back(tempItem);

		tempInt = NULL;
	}


	FILE.close();
}

void Inventory::loadTraits()
{
	traitList.clear();

	std::string tempT;
	std::string tempDes;
	std::string stringToInt;

	Trait* tempTrait = NULL;

	int tempInt;

	std::string fileName = "Traits.txt";
	std::ifstream FILE(fileName);

	while (!FILE.eof())
	{
		std::stringstream converter;

		getline(FILE, tempT, '/');

		getline(FILE, stringToInt);

		getline(FILE, tempDes);

		converter << stringToInt;
		converter >> tempInt;

		tempTrait = new Trait(tempT, tempDes, tempInt);
		traitList.push_back(tempTrait);

		tempInt = NULL;
	}


	FILE.close();
}