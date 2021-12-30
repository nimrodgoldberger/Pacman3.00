#include "NoviceGhost.h"

void NoviceGhost::setDirection(char newDirection)
{
	entityDirection = newDirection;
}

void NoviceGhost::decideGhostDirection(Map& mp, char** theMap, int yDest, int xDest)
{
	static int numOfMoves = 0;
	if (numOfMoves == 20||entityDirection==STAY)
	{
		randDirection();
		numOfMoves = 0;
	}
	numOfMoves++;

}

void NoviceGhost::randDirection()
{
	int randomNumForDirection;
	randomNumForDirection = rand() % 4;
	switch (randomNumForDirection)
	{
	case 0:
	{
		entityDirection = UP;
		break;
	}
	case 1:
	{
		entityDirection = DOWN;
		break;
	}
	case 2:
	{
		entityDirection = LEFT;
		break;
	}
	case 3:
	{
		entityDirection = RIGHT;
		break;
	}
	}
}