#include "Position.h"
Position Position::operator=(Position& newPos)
{
	y = newPos.getY();
	x = newPos.getX();
	return *this;
}
