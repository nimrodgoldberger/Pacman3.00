#include "Pacman.h"

void Pacman::setDirection(char newDirection)
{
	entityDirection = newDirection;
}

void Pacman::printSymbol()const
{
	cout << symbol;
}



char Pacman::move(Map& mp, int pacmanY, int pacmanX,bool colorful,int scoreAndLivesRow)
{
	char nextObject = mp.checkNextMove(y, x, entityDirection);
	switch (entityDirection)
	{
	case UP:
	{
		if (!changeDirectionToStayIfNeeded(nextObject))
		{
			if (nextObject == CRUMBSIGN )
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)/*maybe else if*/
			{
				if (scoreAndLivesRow == 0)
					gotoxy(x, y + 1);
				else
					gotoxy(x, y);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				cout << mp.getSymbolInMap(y, x);
				if (scoreAndLivesRow == 0)
					gotoxy(x,  mp.getRows() - 1);
				else
					gotoxy(x, mp.getRows()-2);
				setEntityYPos(mp.getRows() - 2);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
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
					gotoxy(x,y - 1 );
				setEntityYPos(y - 1);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
			
			/*cout << symbol;*/
		}
		break;
	}
	case DOWN:
	{
		if (!changeDirectionToStayIfNeeded(nextObject))
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
			{
				if (scoreAndLivesRow == 0)
					gotoxy(x, y + 1);
				else
					gotoxy(x, y);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				cout << mp.getSymbolInMap(y, x);
				if (mp.getLineOfScoreBar() == 0)
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, 3);
					else
						gotoxy(x, 2);
					setEntityYPos(2);
				}
				else
				{
					if (scoreAndLivesRow == 0)
						gotoxy(x, 2);
					else
						gotoxy(x, 1);
					setEntityYPos(1);
				}
				
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
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
					gotoxy(x, y+2);
				else
					gotoxy( x,y +1 );
				setEntityYPos(y + 1);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
			
			/*cout << symbol;*/
		}
		break;
	}
	case LEFT:
	{
		if (!changeDirectionToStayIfNeeded(nextObject))
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
			{
				if (scoreAndLivesRow == 0)
					gotoxy(x, y + 1);
				else
					gotoxy(x, y);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				cout << mp.getSymbolInMap(y, x);
				if (scoreAndLivesRow == 0)
					gotoxy(mp.getCols() - 2, y+1);
				else
				gotoxy(mp.getCols() - 2,y);
				setEntityXPos(mp.getCols() - 2);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
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
					gotoxy(x-1, y + 1);
				else
					gotoxy(x - 1, y);
				setEntityXPos(x - 1);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
			
			/*cout << symbol;*/
		}
		break;
	}
	case RIGHT:
	{
		if (!changeDirectionToStayIfNeeded(nextObject))
		{
			if (nextObject == CRUMBSIGN)
			{
				eatCrumb(mp);
			}
			if (nextObject == TUNNEL)
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
				setEntityXPos(1);
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				printSymbol();
				if (colorful)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			}
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
					gotoxy(x+1, y + 1);
				else
					gotoxy(x + 1, y);
				setEntityXPos(x + 1);
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
	return entityDirection;
}