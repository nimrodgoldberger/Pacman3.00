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
	
	virtual char type()const { return symbol; };

};



