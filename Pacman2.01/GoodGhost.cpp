#include "GoodGhost.h"

void GoodGhost::setDirection(char newDirection)
{
	entityDirection = newDirection;
}

void GoodGhost::decideGhostDirection(Map& mp, char** theMap, int yDest,int xDest)
{
	static int numOfMoves = 0;
	static int cycle = rand() % 20;
	static int stupidMoves = 5;
	static bool stupid = false;
	if (numOfMoves == cycle && !stupid)
	{
		randDirection();
		cycle = rand() % 20;
		numOfMoves = 0;
		stupid = true;
	}
	else if (stupid)
	{
		if (numOfMoves==stupidMoves)
		{
			stupid = false;
		}
	}
	else
	{
		int up, down, left, right;
		if (theMap[this->getEntityYPos() - 1][this->getEntityXPos()] != WALL) //tunnel option is irrelenvant
		{
			up = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos() - 1, this->getEntityXPos());
		}
		else
			up = MAX_ROUTE_LEN;

		if (theMap[this->getEntityYPos() + 1][this->getEntityXPos()] != WALL) //tunnel option is irrelenvant
		{
			down = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos() + 1, this->getEntityXPos());
		}
		else
			down = MAX_ROUTE_LEN;

		if (theMap[this->getEntityYPos()][this->getEntityXPos() - 1] != WALL) //tunnel option is irrelenvant
		{
			left = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos(), this->getEntityXPos() - 1);
		}
		else
			left = MAX_ROUTE_LEN;
		if (theMap[this->getEntityYPos()][this->getEntityXPos() + 1] != WALL) //tunnel option is irrelenvant
		{
			right = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos(), this->getEntityXPos() + 1);
		}
		else
			right = MAX_ROUTE_LEN;

		
		entityDirection = chooseDirectionFromShortRoute(up, down, left, right);
	}
	numOfMoves++;
}



void GoodGhost::randDirection()
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