#include <ctime>
#include <cstdlib>

#ifndef DIE_H
#define DIE_H
class Die
{
public:
	Die(int);
	int roll();

	void changeSides(int);

protected:
	int sides = 20;
};

#endif