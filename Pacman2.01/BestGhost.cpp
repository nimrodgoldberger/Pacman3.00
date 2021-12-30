#include "BestGhost.h"


void BestGhost::setDirection(char newDirection)
{
	entityDirection = newDirection;
}

void BestGhost::decideGhostDirection(Map& mp, char** theMap, int yDest, int xDest)
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

	if (theMap[this->getEntityYPos()][this->getEntityXPos()- 1] != WALL) //tunnel option is irrelenvant
	{
		left = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos() , this->getEntityXPos()- 1);
	}
	else
		left = MAX_ROUTE_LEN;
	if (theMap[this->getEntityYPos()][this->getEntityXPos() + 1] != WALL) //tunnel option is irrelenvant
	{
		right = minDistance(mp, theMap, yDest, xDest, this->getEntityYPos() , this->getEntityXPos()+ 1);
	}
	else
		right = MAX_ROUTE_LEN;
	
	
	entityDirection = chooseDirectionFromShortRoute(up, down, left, right);
}





