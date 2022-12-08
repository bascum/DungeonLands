#include <ctime>
#include <cstdlib>
#include "Die.h"

Die::Die(int s)
{
	srand(time(NULL));
	sides = s;
}

Die::Die()
{
	srand(time(NULL));
	sides = 20;
}

int Die::roll()
{
	return rand() % sides + 1;
}

void Die::changeSides(int side)
{
	this->sides;
}