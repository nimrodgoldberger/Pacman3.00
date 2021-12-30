#include "Entity.h"
/*SETTERS*/
Entity::Entity( Position startPos)
{
	setStartingPos(startPos);
}
void Entity::setEntityXPos(int Xpos)
{
	x = Xpos;
}
void Entity::setEntityYPos(int Ypos)
{
	y = Ypos;
}
void Entity::setStartingPos( Position newPos)
{
	startingPos = newPos;
	y = newPos.getY();
	x = newPos.getX();
}

/*GETTERS*/
int Entity::getEntityXPos()const
{
	return x;
}
int Entity::getEntityYPos()const
{
	return y;
}
bool Entity::operator ==(Entity& other) //checks if two Entities share the same coordinates
{
	if (x==other.getEntityXPos() && y==other.getEntityYPos())
	{
		return true;
	}
	return false;
}



bool Entity::changeDirectionToStayIfNeeded(char nextObject)
{
	bool needToStay = false;
	
	if (type()!='@')
	{
		if (nextObject == TUNNEL)
		{
			entityDirection = STAY;
			needToStay = true;

		}
	}
	if (nextObject == WALL)
	{
		entityDirection = STAY;
		needToStay = true;
	}
	return needToStay;
}