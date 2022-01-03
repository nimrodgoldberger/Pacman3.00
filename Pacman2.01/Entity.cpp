#include "Entity.h"
/*SETTERS*/
Entity::Entity(Position startPos)
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
void Entity::setStartingPos(Position newPos)
{
	startingPos = newPos;
	y = newPos.getY();
	x = newPos.getX();
}
/*LOAD FUNCTIONS*/
void Entity::move_load(char direction, char entityType, Map& mp, bool colorful, int scoreAndLivesRow, GameMode gameMode)
{
	char nextObject = mp.checkNextMove(y, x, direction);
	switch (direction)
	{
	case UP:
	{
		if (entityType == 'p')
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)/*maybe else if*/
			{
				if (gameMode != GameMode::loadSilent)
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, y + 1);
					else
						gotoxy(x, y);
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					cout << mp.getSymbolInMap(y, x);
					if (scoreAndLivesRow == 0)
						gotoxy(x, mp.getRows() - 1);
					else
						gotoxy(x, mp.getRows() - 2);

				}
				setEntityYPos(mp.getRows() - 2);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}

			}
			else
			{

				if (gameMode != GameMode::loadSilent)
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
				}

				setEntityYPos(y - 1);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
		}
		else
		{

			if (gameMode != GameMode::loadSilent)
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
			}

			setEntityYPos(y - 1);
			if (gameMode != GameMode::loadSilent)
			{
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
		}
		break;
	}
	case DOWN:
	{
		if (entityType == 'p')
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
			{
				if (gameMode != GameMode::loadSilent)
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, y + 1);
					else
						gotoxy(x, y);

					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					cout << mp.getSymbolInMap(y, x);
				}
				if (mp.getLineOfScoreBar() == 0)
				{
					if (gameMode != GameMode::loadSilent)
					{
						if (scoreAndLivesRow == 0)
							gotoxy(x, 3);
						else
							gotoxy(x, 2);
					}
					setEntityYPos(2);
				}
				else
				{
					if (gameMode != GameMode::loadSilent)
					{
						if (scoreAndLivesRow == 0)
							gotoxy(x, 2);
						else
							gotoxy(x, 1);
					}
					setEntityYPos(1);
				}
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
			else
			{
				if (gameMode != GameMode::loadSilent)
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
				}
				setEntityYPos(y + 1);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
		}
		else
		{
			if (gameMode != GameMode::loadSilent)
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
			}
			setEntityYPos(y + 1);
			if (gameMode != GameMode::loadSilent)
			{
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
		}
		/*cout << symbol;*/
		break;
	}
	case LEFT:
	{
		if (entityType == 'p')
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
			{
				if (gameMode != GameMode::loadSilent)
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, y + 1);
					else
						gotoxy(x, y);
				}
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					cout << mp.getSymbolInMap(y, x);

					if (scoreAndLivesRow == 0)
						gotoxy(mp.getCols() - 2, y + 1);
					else
						gotoxy(mp.getCols() - 2, y);
				}
				setEntityXPos(mp.getCols() - 2);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
			else
			{
				if (gameMode != GameMode::loadSilent)
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
				}
				setEntityXPos(x - 1);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
			/*cout << symbol;*/
		}
		else
		{
			if (gameMode != GameMode::loadSilent)
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
			}
			setEntityXPos(x - 1);
			if (gameMode != GameMode::loadSilent)
			{
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
		}
		/*cout << symbol;*/
		break;
	}
	case RIGHT:
	{
		if (entityType == 'p')
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
			{
				if (gameMode != GameMode::loadSilent)
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, y + 1);
					else
						gotoxy(x, y);

					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					cout << mp.getSymbolInMap(y, x);

					if (scoreAndLivesRow == 0)
						gotoxy(1, y + 1);
					else
						gotoxy(1, y);
				}
				setEntityXPos(1);
				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
			else
			{

				if (gameMode != GameMode::loadSilent)
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
				}
				setEntityXPos(x + 1);

				if (gameMode != GameMode::loadSilent)
				{
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					printSymbol();
					if (colorful)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
			}
		}
		else
		{

			if (gameMode != GameMode::loadSilent)
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
			}
			setEntityXPos(x + 1);
			if (gameMode != GameMode::loadSilent)
			{
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
		}
		break;
	}
	case STAY:
	{
		break;
	}
}
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
	if (x == other.getEntityXPos() && y == other.getEntityYPos())
	{
		return true;
	}
	return false;
}



bool Entity::changeDirectionToStayIfNeeded(char nextObject)
{
	bool needToStay = false;

	if (type() != '@')
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