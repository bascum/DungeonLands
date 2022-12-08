#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Inventory.h"
#include "WeightedDie.h"

using namespace std;

Inventory myInv; //Inv is global since there will only be one per program 

void addItem(); //This will add a specific item that comes from user input


int main()
{

	int choice = 0;

	while (choice != 4)
	{
		choice = 0;

		myInv.displayInv();

		cout << "\n***MENU***\n\n";
		cout << "1) Add a specific Item\n";
		cout << "2) Add a Random Item\n";
		cout << "3) Delete Item\n";
		cout << "4) END\n";
		cin >> choice;

		switch (choice)
		{
			case 1:
				addItem();
				break;

			case 2:
				myInv.addRandItem();
				break;

			case 3:
				myInv.delItem();
				break;

			case 4:
				break;

			default:
				cout << "\nInput not recognized\n";
				break;
		}
	}
}

void addItem()// takes user input and passes into the inventory class.
{
	string tempType;
	int dmgDie;
	char choice = 'N';

	char clearBuffer;

	while (choice == 'N' || choice == 'n')
	{
		cout << "\nPlease enter the type of Item you would like to add: ";
		cin.clear();
		cin.ignore();
		getline(cin, tempType);

		cout << "\nPlease enter the Damage Die for this weapon: ";
		cin >> dmgDie;

		cout << "Your item will be a, " << tempType << ", with a damage die of, " << dmgDie << ". Is this correct? (Y/N): ";
		cin >> choice;

		if (choice == 'Y' || choice == 'y')
		{
			myInv.addItem(tempType, dmgDie);
		}
	}
}