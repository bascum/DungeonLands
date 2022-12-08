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
	//Constructor runs these 2 funtions to pull data from txt files and populate the vectors
	loadItemTypes();
	loadTraits();
}

void Inventory::addItem(std::string t, int d)
/*Eventually this will be editted to take no parameters and have the user input the */
{
	char chChoice; //Function needs to take both an int choice and a Char choice so initialize those
	int intChoice = 0;

	Item* tPtr = NULL; //Initialize the item pointer that will be used to make the item that is then given to the node


	std::cout << "\nWill the Item have a trait? (Y/N): "; //If the user selects Y they are given a list of traits to pick.
	std::cin >> chChoice;									//otherwise they will not have a trait


	if (chChoice == 'Y' || chChoice == 'y')
	{
		std::cout << "\n\n*** Please select a trait from the list below ***\n";
		showTraitList();
		std::cin >> intChoice;

		tPtr = new Item(t, d, traitList[intChoice - 1]);//Item is made and given a pointer
	}
	else
	{
		tPtr = new Item(t, d); //Same item being made but without giving it the trait
	}

	Node* newItem = new Node(*tPtr); //Node is made by passing through the item

	if (head == NULL)				//IF there are already nodes in the list adds the node to the top otherwise sets the node as top
	{
		head = newItem;
	}
	else if (head != NULL)
	{
		newItem->next = head;
		head = newItem;
	}
	invSize++; //trasks amount of Nodes/ Items
}

void Inventory::addRandItem() 
{
													//Familiar user input
	char userChoice = NULL;
	std::cout << "\n***Is this a Normal Item or a Special Item? (N/S): ";


	std::cin.ignore();								//Had an issue with the buffer keeping characters so cleared it
	std::cin.clear();								//Then took the user inut character.
	std::cin >> userChoice;

	if (userChoice == 'N' || userChoice == 'n')
	{
		Die tempD20(itemTypeList.size());			//A die is made to generate random numbers between 1 - the number of item types
		
		int roll = tempD20.roll() - 1;				//Die is rolled to figure out which item it will be (This could be directly within the next statement)
		
		
		Item tempItem(itemTypeList[roll]->getType(), itemTypeList[roll]->getDmgDie());
		//New Item is made using the roll. Probably could just pass a dereferenced itemTypeList[i] to the next statement
		
		Node* newItem = new Node(tempItem);			//Create a node with the recently created item

		if (head == NULL)							//Add node to the top of list (Familiar stuff)
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
		Die d20(20);								//Copy and paste of previous code that will make a die
		int unweightedRoll = d20.roll() - 1;		//Then roll it

		WeightedDie wD20(20);						//Since the user wanted their item to have a trait that means it needs a 
		int rarityMax = wD20.genRoll() / 5;			//trait. Traits are organized into rarities so the users are not given a great trait
													//too often
		//Above will generate a random number between 1 and 20 with a much higher probability of a 1 than a 20. then the answer is divided by
		//5 to get a weighted roll between 1 and 5

		Item tempItem(itemTypeList[unweightedRoll]->getType(), itemTypeList[unweightedRoll]->getDmgDie(), getRandTrait(rarityMax) );
		// Same as no trait but also passes a trait* as last parameter using a special private funtion that takes the max rarity
		
		
		Node* newItem = new Node(tempItem);			//Nothing new here just creating new node and adding to top of list

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
	else
	{
		invSize--;
	}
	invSize++;										//Item was added so track that
}

void Inventory::delItem()
{
	displayInv();									//The inventory will most likely be on screen but still want to show it again


	int choice = 0;									//User will have multiple choices so make those variables
	char yesNo = 'n';
	
	std::cout << "\nPlease input the position of the item you would like to delete: ";
	std::cin >> choice;								//inv is displayed with numbered positions so this takes the choice of which
													//position member to delete

	if (choice > 0 && choice <= invSize)			//if user puts negative or too high nothing happens
	{
		Node* tempNode = findNode(choice - 1);		//Private funtion to return the mem address of the node	


		std::cout << "\nAre you sure you would like to delete (" << choice << ") " << tempNode->data.getType() << " (Y/N): ";
		std::cin >> yesNo;							//Ask user to confirm before deleting
			
		if (yesNo == 'Y' || yesNo == 'y')			//Delete node if user wants to
		{
			delNode(choice - 1);
		}
	}
}

void Inventory::displayInv()
{
	insertionSort();
	Node* tempHead = head;
	int count = 1;
	if (invSize > 0)								//if there is an item in inv displays a list of all items
	{
		do {
			std::cout << "\n" << count << ") NAME: " << tempHead->data.getType() << ". | Rarity: " << tempHead->data.getRarity() << "\n   DMG : " << tempHead->data.getDmgDie() << "\n   Trait : " << tempHead->data.getTraitName();
			tempHead = tempHead->next;
			count++;
		} while (tempHead != NULL);
	}
}

void Inventory::showTraitList()						//This is a private function that shows the traits for the user to choose from
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
													//Takes the contents of a txt file and creates Objects to load into a vector
void Inventory::loadItemTypes()
{
	itemTypeList.clear();							//Ensures there is no junk in the vector. I belive vecotrs always are clear but still

	std::string tempT;								//Initialize all variables
	std::string stringToInt;

	Item* tempItem = NULL;

	int tempInt;

	std::string fileName = "Melee_Items.txt";
	std::ifstream FILE(fileName);					//open the file for input into the program

	while (!FILE.eof())
	{
		std::stringstream converter;				//make a stringstream object to later use to convert a strint to an int
													//Could not use aiot() for some reason but have since forgotten the reason


		getline(FILE, tempT, '/');					//The way the file is formatted it will contain the name of the item followed by a 
													//slash. 

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
		myTrait = traitList[randTrait.roll() - 1];
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

void Inventory::insertionSort()
{
	sorted = NULL;
	Node* current = head;

	while (current != NULL) {
		Node* next = current->next;

		sort(current);

		current = next;
	}
	head = sorted;
}

void Inventory::sort(Node* h)
{
	if (sorted == NULL || sorted->data.getRarity() >= h->data.getRarity()) {
		h->next = sorted;
		sorted = h;
	}
	else {
		Node* current = sorted;
		while (current->next != NULL && current->next->data.getRarity() < h->data.getRarity()) {
			current = current->next;
		}
		h->next = current->next;
		current->next = h;
	}
}