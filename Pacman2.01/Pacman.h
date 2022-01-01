#pragma once
#include "Entity.h"
#include "Map.h"
#define FREE ' '

class Pacman : public Entity
{
private:
	char symbol='@';
public:
	Pacman( Position& startPos) : Entity(startPos) {}
	Pacman() = default;
	~Pacman(){};
	char move(Map& mp,int pacmanY, int pacmanX,bool colorful, int scoreAndLivesRow);
	void setDirection(char newDirection);
	void printSymbol()const;
	void eatCrumb(Map& mp)
	{
		mp.setSymbolInMap(this->y,this->x, ' ');/*WHY NOT WITH protected in Entity x,y*/

	}
	virtual char type()const { return symbol; };

};



