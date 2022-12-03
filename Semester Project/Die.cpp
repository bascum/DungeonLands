#include <ctime>
#include <cstdlib>
#include "Die.h"

Die::Die(int s)
{
	sides = s;
}

Die::Die()
{
	sides = 20;
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