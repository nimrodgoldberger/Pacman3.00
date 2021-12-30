#pragma once

#include "Position.h"
#include "Map.h"
#define UP 'w'
#define DOWN 'x'
#define LEFT 'a'
#define RIGHT 'd'
#define STAY 's'

class Entity/*base class of all moving objects(pacman,ghost,fruit)*/
{

protected:
	int x=0;/*entity's current x*/
	int y=0;/*entity's current y*/
	Position startingPos;/*starting position also used after collision between pacman and ghost*/
	char entityDirection = STAY;/*direction*/
	
	
public:
	Entity( Position startPos); /*ctor*/
	Entity() = default;
	virtual ~Entity(){};
	/*SETTERS*/
	void setEntityXPos(int Xpos);/*set Entity's X*/
	void setEntityYPos(int Ypos);/*set Entity's Y*/
	
	void setStartingPos( Position newPos);
	/*GETTERS*/
	int getEntityXPos()const;/*Gets Entity's X*/
	int getEntityYPos()const;/*Gets Entity's Y*/
	inline char getEntityDirection()const { return entityDirection; }
	
	/*VIRTUAL*/
	virtual void move(Map& mp ,int pacmanY,int pacmanX,bool colorful,int scoreAndLivesRow)=0;
	virtual void printSymbol()const = 0;
	
	virtual void setDirection(char newDirection)=0;

	bool operator ==(Entity& other);
	bool changeDirectionToStayIfNeeded(char nextObject);
	inline Position getStartingPos()const { return startingPos; }

	virtual char type()const =0;
	void gotoxy(int x, int y)
	{
		HANDLE hConsoleOutput;
		COORD dwCursorPosition;
		cout.flush();
		dwCursorPosition.X = x;
		dwCursorPosition.Y = y;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
	}
};