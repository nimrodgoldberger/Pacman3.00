#include "Map.h"
#include <fstream>


#define MAXLINE 100

////Map::Map()
////{
////	char def = CRUMB;
////	/*initializes all the board with crumbs*/
////	for (size_t i = 0; i < 27; i++)
////	{
////		for (size_t j = 0; j < 17; j++)
////			TheMap[i][j] = def;
////	}
////	/*fills board with walls*/
////	for (short j = 1; j <= 13; j++)
////	{
////		for (short i = 1; i <= 8; i++)
////		{
////			if (j == 13 || i == 8)/*Borders of the board*/
////			{
////				
////				TheMap[13 + j][8 + i] = WALL;
////				TheMap[13 + j][8 - i] = WALL;
////				TheMap[13 - j][8 + i] = WALL;
////				TheMap[13 - j][8 - i] = WALL;
////			}
////			else if (j == 1)
////			{
////				if (i != 3)
////				{
////
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 2)
////			{
////				if (i == 6)
////				{
////
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 3 || j == 5)
////			{
////				if (i == 1 || i == 3 || i == 4 || i == 6)
////				{
////
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 4)
////			{
////				if (i == 1 || i == 3 || i == 4)
////				{
////
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 6)
////			{
////				if (i == 1 || i == 6)
////				{
////
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 7 || j == 10)
////			{
////				if (i == 1 || i == 2 || i == 4 || i == 6)
////				{
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 8)
////			{
////				if (i == 1 || i == 2 || i == 4)
////				{
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 9)
////			{
////				if (i == 4 || i == 6)
////				{
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 11)
////			{
////				if (i == 2 || i == 4 || i == 6)
////				{
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////			else if (j == 12)
////			{
////				if (i == 2 || i == 6)
////				{
////					TheMap[13 + j][8 + i] = WALL;
////					TheMap[13 + j][8 - i] = WALL;
////					TheMap[13 - j][8 + i] = WALL;
////					TheMap[13 - j][8 - i] = WALL;
////				}
////			}
////		}
////	}
////	/*completion of rest of board */
////	
////	TheMap[13][6] = WALL;
////	
////	TheMap[13][10] = WALL;
////	
////	TheMap[14][8] = WALL;
////	
////	TheMap[13][0] = TUNNEL;
////	
////	TheMap[13][16] = TUNNEL;
////	
////	TheMap[26][8] = TUNNEL;
////	
////	TheMap[0][8] = TUNNEL;
////};

Map::Map(string fileName)
{
	ifstream mapFile(fileName, ios_base::in);
	while (!mapFile)
	{
		cout << endl << "File not found!" << endl << "Please enter a correct File Name.(example: pacman_03.screen)" << endl;
		cin >> fileName;
		cout << fileName;
		mapFile=ifstream(fileName, ios_base::in);
	}
	char* tempStr= new char[MAXLINE];
	string s;
	while (!mapFile.eof()) {
		mapFile.getline(tempStr, MAXLINE);
		s.assign(tempStr);
		if (rows == 0&& s.length()!=1)
			cols = (int)s.length();
		if (s.length() == 1)//line of &
		{
			lineOfScoreBar = rows;
		}
		else
		{
			rows++;
		}
	}
	TheMap = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		TheMap[i] = new char[cols];
	}
	mapFile.seekg(0);
	if(lineOfScoreBar==0)
		mapFile.getline(tempStr, MAXLINE);
	int j = 0;
	while (j<rows) {
		mapFile.getline(tempStr, MAXLINE);
		s.assign(tempStr);
		int i = 0;
		while (i < cols)
		{	
			TheMap[j][i] = deCodeFile(s[i]);
			switch (TheMap[j][i])
			{
			case PACMAN:
			{
				pacManStartingPos.setY(j);
				pacManStartingPos.setX(i);
				TheMap[j][i] = FREE;
				break;
			}
			case GHOSTSIGN:
			{
				Position temp(j, i);
				GhostArr.push_back(temp);
				//cout << "number of ghosts" << GhostArr.size() << endl;/*check check check*/
				TheMap[j][i] = CRUMBSIGN;
				break;
			}
			default:
				break;
			}
			/*update Pacman starting pos*/
			i++;
		}
		j++;
	}
	if (countTunnels%2 !=0)
	{
		cout << " ERROR YOU HAVE AN ODD NUMBER OF TUNNELS" << endl;
	}
	mapFile.close();
}
char Map::deCodeFile(char c)
{
	switch (c)
	{
	case TUNNEL: {
		countTunnels++;
		return c;
	}
	case WALL:
		return c;
	case PACMAN:
	{
		/*if (isThereAsinglePacman)
		{
			cout << " ERROR YOU HAVE MORE THAN ONE PACMAN" << endl << " WE WILL TURN IT INTO A WALL" << endl;
			return WALL;
		}
		isThereAsinglePacman = true;*/
		return c;
	}
	case GHOST:
	{
		numOfCrumbs++;
		return GHOSTSIGN;
	}
	case EMPTY:
		return FREE;
	case CRUMB:
	{
		numOfCrumbs++;
		return CRUMBSIGN;
	}
	default:
		cout << "ERROR!!! Illegal Characters from file!!" << endl;
		return WALL;
	}
}
char Map::checkNextMove(int y, int x, char direction)
{
	char nextObject = FREE;
	switch (direction)
	{
	case UP:
	{
		nextObject = getSymbolInMap(y - 1, x);
		break;
	}
	case DOWN:
	{
		nextObject = getSymbolInMap(y + 1, x);
		break;
	}
	case LEFT:
	{
		nextObject = getSymbolInMap(y, x - 1);

		break;
	}
	case RIGHT:
	{
		nextObject = getSymbolInMap(y, x + 1);

		break;
	}
	case STAY:
	{
		nextObject = getSymbolInMap(y, x);
		break;
	}
	}
	return nextObject;
}

void Map::setColorChoice()
{
	char colorChoice = 't';
	system("CLS");
	cout << "Do you want to play with Colors?" << endl << "For YES press y" << endl << "For NO press n" << endl;
	while (colorChoice != 'y' && colorChoice != 'n')
		colorChoice = _getch();
	if (colorChoice == 'n')
		inColor = BLACKANDWHITE;
	else
		inColor = COLORFUL;
	system("CLS");
	/*inColor = COLORFUL;*/
}
bool Map::doesThePlayerWantColors()
{
	return inColor;
}
//void Map::printMap()
//{
//	for (size_t i = 0; i < 27; i++)
//	{
//		for (size_t j = 0; j < 17; j++)
//		{
//			if (TheMap[i][j] == WALL)
//			{
//				if (inColor)
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
//				cout << TheMap[i][j];
//			}
//			else
//			{
//				if (inColor)
//					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
//				cout <<TheMap[i][j];
//			}
//		}
//		cout << endl;
//	}
//}
void Map::printMap()
{
	if (lineOfScoreBar==0)
		gotoxy(0,1);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j <cols; j++)
		{
			if (TheMap[i][j] == WALL)
			{
				if (inColor)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
				cout << TheMap[i][j];
			}
			else
			{
				if (inColor)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				cout << TheMap[i][j];
			}
		}
		cout << endl;
	}
}

char Map::getSymbolInMap(int y, int x)
{
	return TheMap[y][x];
}
void Map::setSymbolInMap(int y, int x, char newType)/*laasot tirgum yaffe*/
{
	TheMap[y][x]=newType;
}

Position Map::getPacmanStartPos()
{
	return pacManStartingPos;
}
Position Map::getGhostStartPos(int index)
{
	return GhostArr[index];
}
