#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Inventory.h"
#include "WeightedDie.h"

using namespace std;

Inventory myInv;

void addItem();


int main()
{

	int choice = 0;

	while (choice != 4)
	{
		choice = 0;
		cout << "\n***MENU***\n\n";
		cout << "1) Add a specific Item\n";
		cout << "2) Add a Random Item\n";
		cout << "3) View Inventory\n";
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

		}
	}
}

void addItem()
{
	string tempType;
	int dmgDie;
	char choice;

	char clearBuffer;

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