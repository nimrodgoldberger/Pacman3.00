#include "Fruit.h"
char Fruit::move(Map& mp, int pacmanY, int pacmanX,bool colorful, int scoreAndLivesRow)
{
	randDirection();
	char nextObject = mp.checkNextMove(y, x, entityDirection);
	switch (entityDirection)
	{
	case UP:
	{
		if (nextObject == TUNNEL || nextObject == WALL)
			entityDirection = STAY;
		else
		{
			if (scoreAndLivesRow == 0)
				gotoxy(x, y + 1);
			else
				gotoxy(x, y);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			cout << mp.getSymbolInMap(y, x);
			if (scoreAndLivesRow == 0)
				gotoxy(x, y);
			else
				gotoxy(x, y - 1);
			setEntityYPos(y - 1);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			printSymbol();
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
		break;
	}
	case DOWN:
	{
		if (nextObject == TUNNEL || nextObject == WALL)
			entityDirection = STAY;
		else
		{
			if (scoreAndLivesRow == 0)
				gotoxy(x, y + 1);
			else
				gotoxy(x, y);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			cout << mp.getSymbolInMap(y, x);
			if (scoreAndLivesRow == 0)
				gotoxy(x, y + 2);
			else
				gotoxy(x, y + 1);
			setEntityYPos(y + 1);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			printSymbol();
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
		break;
	}
	case LEFT:
	{
		if (nextObject == TUNNEL || nextObject == WALL)
			entityDirection = STAY;
		else
		{
			if (scoreAndLivesRow == 0)
				gotoxy(x, y + 1);
			else
				gotoxy(x, y);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			cout << mp.getSymbolInMap(y, x);
			if (scoreAndLivesRow == 0)
				gotoxy(x - 1, y + 1);
			else
				gotoxy(x - 1, y);
			setEntityXPos(x - 1);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			printSymbol();
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
		break;
	}
	case RIGHT:
	{
		if (nextObject == TUNNEL || nextObject == WALL)
			entityDirection = STAY;
		else
		{
			if (scoreAndLivesRow == 0)
				gotoxy(x, y + 1);
			else
				gotoxy(x, y);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			cout << mp.getSymbolInMap(y, x);
			if (scoreAndLivesRow == 0)
				gotoxy(x + 1, y + 1);
			else
				gotoxy(x + 1, y);
			setEntityXPos(x + 1);
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			printSymbol();
			if (colorful)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
		break;
	}
	}
	lifeTime--;
	return entityDirection;
}



void Fruit::setDirection(char newDirection)
{
	entityDirection = newDirection;
}

void Fruit::randDirection()
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

int Fruit::getLifeTime()const
{
	return lifeTime;
}
void Fruit::setLifeTime()
{
	lifeTime= (rand() % 20)+30;
}
void Fruit::ZeroLifeTime()
{
	lifeTime = 0;
}
void Fruit::setSymbol()
{
	symbol =(( rand() % 5)+5)+'0';
}