#include <ctime>
#include <cstdlib>
#include "Die.h"

#ifndef WEIGHTEDDIE_H
#define WEIGHTEDDIE_H

class WeightedDie : public Die
{
public:
	WeightedDie(int = 0, int = 20);

	void changeWeight(int);
	//void changeSides(int);
	int genRoll();
	
private:
	int weightMod = 0;
	int weights[20] = { NULL };
	int sum = 0;

	/*Below are used in the random weighted number and shouldnt be used anywhere else*/
	int checkRand(int, int = 0, int = 0);
	void genWeights();
};

#endif