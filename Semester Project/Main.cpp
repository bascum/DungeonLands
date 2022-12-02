#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Inventory.h"
#include "WeightedDie.h"




using namespace std;


int main()
{
	Inventory myInv;

	myInv.addItem("sword", 6);

	myInv.displayInv();

}
