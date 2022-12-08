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
	invSize++;
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
		int rarityMax = wD20.genRoll() / 5;

		Item tempItem(itemTypeList[unweightedRoll]->getType(), itemTypeList[unweightedRoll]->getDmgDie(), getRandTrait(rarityMax) );

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
	invSize++;
}

void Inventory::delItem()
{
	displayInv();
	int choice = 0;
	char yesNo = 'n';
	
	std::cout << "\nPlease input the position of the item you would like to delete: ";
	std::cin >> choice;

	if (choice > -1 && choice <= invSize)
	{
		Node* tempNode = findNode(choice - 1);
		std::cout << "\nAre you sure you would like to delete (" << choice << ") " << tempNode->data.getType() << " (Y/N): ";
		std::cin >> yesNo;

		if (yesNo == 'Y' || yesNo == 'y')
		{
			delNode(choice - 1);
		}
	}
}

void Inventory::displayInv()
{
	Node* tempHead = head;
	int count = 1;
	if (invSize > 0)
	{
		do {
			std::cout << "\n" << count << ") NAME: " << tempHead->data.getType() << "\n   DMG : " << tempHead->data.getDmgDie() << "\n   Trait : " << tempHead->data.getTraitName();
			//if (tempHead->next != NULL)
			tempHead = tempHead->next;
			count++;
		} while (tempHead != NULL);
	}
}

void Inventory::showTraitList()
{
	for (int i = 0; i < traitList.size(); i++)
	{
		std::cout << std::endl << i + 1 << ") " << traitList[i]->name << " : Required Rarity (" << traitList[i]->req << "\n----(" << traitList[i]->traitDescription << std::endl;
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

Trait* Inventory::getRandTrait(int max)
{
	Die randTrait(traitList.size());

	Trait* myTrait = traitList[randTrait.roll() - 1];

	while (myTrait->req > max)
	{
		myTrait = traitList[randTrait.roll()];
	}

	return myTrait;
}

void Inventory::delNode(int pos)
{
	int count = 0;
	Node* prevNode = NULL;
	Node* tempNode = head;
	Node* nextNode = tempNode->next;

	while (count != pos)
	{
		prevNode = tempNode;
		tempNode = tempNode->next;
		nextNode = tempNode->next;
		count++;
	}
	if (count == pos)
	{
		prevNode->next = nextNode;
		delete tempNode;
	}
	invSize--;
}

Node* Inventory::findNode(int pos)
{
	int count = 0;
	Node* tempNode = head;

	while (count != pos)
	{
		tempNode = tempNode->next;
		count++;
	}
	
	if (tempNode != head && pos != 0)
	{
		return tempNode;
	}
	else if (tempNode == head && pos == 0)
	{
		return tempNode;
	}
	else
	{
		throw "Error in Finding Node";
	}
}