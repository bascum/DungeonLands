#include <ctime>
#include <cstdlib>
#include "Die.h"

Die::Die(int s)
{
	sides = s;
}

int Die::roll()
{
	srand(time(NULL));
	return rand() % sides + 1;
}

void Die::changeSides(int side)
{
	this->sides;
}