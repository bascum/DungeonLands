#include <ctime>
#include <cstdlib>
#include "Die.h"
#include "WeightedDie.h"

WeightedDie::WeightedDie(int wM, int s) : Die(s)
{
	weightMod = wM;
}

void WeightedDie::changeWeight(int w)
{
	weightMod = w;
}

void WeightedDie::genWeights()
/*This function uses a sin wave to generate a function that generates weights based on a sin wave that
	Range between 1 and 1000*/
{
	double weightModMultiplier = 1.6 / 10; // allows the weight mod to be set to any value between 1 and 20//
	// The peak of the graph and thus the most common weight follows

	sum = 0;
	for (int i = 0; i < 20; i++)
	{
		weights[i] = ((5 * (sin((i / 6.4258) + (1.6 - (weightMod * weightModMultiplier)))) + 5) * 100);//Full of magic numbers to get a function I want.
		//weightMod affects the peak of the sin wave so the user can eventually change how good the gear they 
		//generate is
		sum = sum + weights[i];
	}
}

int WeightedDie::genRoll()
{
	genWeights();
	int rawRoll = rand() % sum + 1;
	return checkRand(rawRoll);
}

int WeightedDie::checkRand(int rawRoll, int tempSum, int count)
{
	if (rawRoll <= tempSum + weights[count])
	{
		return count + 1;
	}
	else {
		return checkRand(rawRoll, tempSum + weights[count], count + 1);
	}
}