#include "Game.h"

/*CONSTRUCTOR*/
Game::Game(string fileName,int& sumOfScores) :map(Map(fileName))
{
	sumOfLastScores = sumOfScores;
	score = 0;
	livesLeft = 3;
	winningScore = map.getNumOfCrumbs();
	pacman.setStartingPos(map.getPacmanStartPos());
}
/*FUNCTIONS*/
bool Game::startGame(int& sumOfScores)
{
	bool GameOn = true, isGamePaused = false,moveGhost=true,collision=false;
	char temp = 0;
	int fruitCoolDown = 0;

	while (GameOn) 
	{
		while (!isGamePaused)
		{
			while (!_kbhit() && livesLeft > 0 && score < winningScore && !collision && fruitCoolDown>0)
			{
				if (getSymbol(pacman.getEntityYPos(),pacman.getEntityXPos()) == CRUMBSIGN)
				{
					map.setSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos(), FREE);
					score++;
					printScoreAndLives(map.getLineOfScoreBar());
				}
				
				pacman.move(map,pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(),map.getLineOfScoreBar());
				
				
				if (fruit != nullptr)
				{
					if (*fruit == pacman)
					{
						winningScore += (fruit->type() - '0');
						score += (fruit->type() - '0');
						delete[] fruit;
						fruit = nullptr;
						printScoreAndLives(map.getLineOfScoreBar());
					}
				}
				for (GhostBase* iterator : ghostArray)
				{
					if (pacman == *iterator)
					{
						collision = true;
						break;
					}
				}
				if(moveGhost)
				{
					if (fruit != nullptr)
					{
						
						fruit->move(map, pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(),  map.getLineOfScoreBar());
						
						
						if (*fruit==pacman)
						{
							winningScore += (fruit->type() - '0');
							score += (fruit->type() - '0');
							if ( map.getLineOfScoreBar()==0)
								gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos()+1);
							else
								gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos());
							if (map.doesThePlayerWantColors())
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
							pacman.printSymbol();
							//cout << pacman.type();
							if (map.doesThePlayerWantColors())
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
							printScoreAndLives(map.getLineOfScoreBar());
							delete[] fruit;
							fruit = nullptr;
						}
					}
						
					for (GhostBase* iterator : ghostArray)
					{
						if (fruit != nullptr)
						{
							if (*iterator == *fruit)
							{
								if (map.getLineOfScoreBar() == 0)
									gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos() + 1);
								else
									gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos());
								if (map.doesThePlayerWantColors())
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
								iterator->printSymbol();
								if (map.doesThePlayerWantColors())
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
								delete[] fruit;
								fruit = nullptr;
							}
						}
						
						(*iterator).move(map,pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(), map.getLineOfScoreBar());

						
						if (*iterator == pacman)
						{
							collision = true;
							break;
						}
						if (fruit != nullptr)
						{
							if (*iterator == *fruit)
							{
								if (map.getLineOfScoreBar() == 0)
									gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos() + 1);
								else
									gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos());
								if (map.doesThePlayerWantColors())
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
								iterator->printSymbol();
								if (map.doesThePlayerWantColors())
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
								delete[] fruit;
								fruit = nullptr;
							}
						}
					}
					moveGhost = false;
					fruitCoolDown--;
				}
				else
					moveGhost = true;
				
				if (fruit!=nullptr)
				{
					if (fruit->getLifeTime() == 0)
					{
						if (map.getLineOfScoreBar() == 0)
							gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos() + 1);
						else
							gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos());
						
						if (map.doesThePlayerWantColors())
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
						cout << map.getSymbolInMap(fruit->getEntityYPos(), fruit->getEntityXPos());/*NIMROD*/
						delete[] fruit;
						fruit = nullptr;
					}
				}
				
				Sleep(250);
			}
			if (fruitCoolDown==0)
			{
				fruit = new Fruit(setFruitStartingPos());
				fruitCoolDown = fruit->getLifeTime() + (rand() % 20) + 30;
			}
			if (collision)
			{
				setNumOfLives();
				printScoreAndLives(map.getLineOfScoreBar());
				if (map.getLineOfScoreBar() == 0)
					gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos()+1);
				else
					gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
				cout << map.getSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos());/*NIMROD*/
				pacman.setEntityXPos(pacman.getStartingPos().getX());
				pacman.setEntityYPos(pacman.getStartingPos().getY());
				if (map.getLineOfScoreBar() == 0)
					gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos() + 1);
				else
					gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				pacman.printSymbol();
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				pacman.setDirection(STAY);
				for (GhostBase* iterator : ghostArray)
				{
					if (map.getLineOfScoreBar() == 0)
						gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos()+1);
					else
						gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos());
					cout << map.getSymbolInMap((*iterator).getEntityYPos(), (*iterator).getEntityXPos());
					(*iterator).setEntityXPos((*iterator).getStartingPos().getX());
					(*iterator).setEntityYPos((*iterator).getStartingPos().getY());
					if (map.getLineOfScoreBar() == 0)
						gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos() + 1);
					else
						gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos());
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					(*iterator).printSymbol();
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
				}
				collision = false;
			}
			
			if (livesLeft == 0)/*LOST*/
			{
				system("CLS");
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				cout << "YOU LOST..." << endl <<"YOUR SCORE WAS: "<< score << endl;
				GameOn = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
				break;
			}
			else if (score == winningScore)/*WON*/
			{
				system("CLS");
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				cout << "YOU WON!! CONGRATS!" << endl <<"YOUR SCORE IS: "<< score << endl;
				GameOn = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
				break;
			}
			else {
				temp = getKey(temp);
				if (temp == ESC)
					isGamePaused = true;
				else
					pacman.setDirection(temp);
			}
		}
		if (isGamePaused) {
			system("CLS");
			if (map.doesThePlayerWantColors())
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			cout << endl << " The game is Paused."<<endl<<  "Press ESC continue";
			if (map.doesThePlayerWantColors())
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
			char go = 0;
			go = getKey(go);
			while (go != ESC)
				go = getKey(go);
			isGamePaused = false;
			system("CLS");
			map.printMap();
			printScoreAndLives(map.getLineOfScoreBar());
		}
		
	}
	sumOfScores += score;
	if (livesLeft == 0)
	{
		return false;
	}
	else 
		return true;
		
}


bool Game::begin(int& sumOfScores)
{
	askGhostLevel();
	map.setColorChoice();
	map.printMap();
	if (map.getLineOfScoreBar() == 0)
		gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos()+1);
	else
		gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
	if (map.doesThePlayerWantColors())
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
	pacman.printSymbol();
	if (map.doesThePlayerWantColors())
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
	printScoreAndLives(map.getLineOfScoreBar());
	
	for (int i = 0; i < map.getGhostArr().size(); i++)
	{
		if (difficultyLevel == ghostType::Novice)
		{
			NoviceGhost* casper = new NoviceGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (map.getLineOfScoreBar() == 0)
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY()+1);
			else
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
			if (map.doesThePlayerWantColors())
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			(*casper).printSymbol();
		}
		if (difficultyLevel == ghostType::Good)
		{
			GoodGhost* casper = new GoodGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (map.getLineOfScoreBar() == 0)
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY() + 1);
			else
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
			if (map.doesThePlayerWantColors())
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			(*casper).printSymbol();
		}
		if (difficultyLevel == ghostType::Best)
		{
			BestGhost* casper = new BestGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (map.getLineOfScoreBar() == 0)
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY() + 1);
			else
				gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
			if (map.doesThePlayerWantColors())
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
			(*casper).printSymbol();
		}
	}
	return startGame(sumOfScores);
}

void Game::askGhostLevel()
{
	char levelChoice = 't';
	system("CLS");
	cout << "Choose Difficulty Level: " << endl << "For Novice press 1" << endl << "For Normal press 2" << endl << "For Hard press 3" << endl;
	while (levelChoice != '1' && levelChoice != '2'&& levelChoice!='3')
		levelChoice = _getch();
	if (levelChoice == '1')
		difficultyLevel = ghostType::Novice;
	else if (levelChoice == '2')
		difficultyLevel = ghostType::Good;
	else
		difficultyLevel = ghostType::Best;
	system("CLS");

}
int Game::getLivesLeft()const
{
	return livesLeft;
}
int Game::getScore()const
{
	return score;
}
/*setters*/
void Game::setScore()
{
	score++;
}
void Game::setNumOfLives()
{
	livesLeft--;
}

char Game::getKey(char c)const
{
	char KeyStroke = _getch();
	switch (KeyStroke)
	{
	case 'w':
	case 'W':
	{
		KeyStroke = UP;
		break;
	}
	case 'd':
	case 'D':
	{
		KeyStroke = RIGHT;
		break;
	}
	case 'a':
	case 'A':
	{
		KeyStroke = LEFT;
		break;
	}
	case 'x':
	case 'X':
	{
		KeyStroke = DOWN;
		break;
	}
	case 's':
	case 'S':
	{
		KeyStroke = STAY;
		break;
	}
	case 27:
	{
		KeyStroke = 27;/*ESC to pause menu*/
		break;
	}
	default:
	{
		KeyStroke = c;/*if unvalid direction, continue with last one*/
		break;
	}
	}
	return (KeyStroke);
}
char Game::getSymbol(int y, int x)
{
	return map.getSymbolInMap(y, x);
}
void Game::printScoreAndLives(int lineOfScoreBar)
{
	gotoxy(0, lineOfScoreBar);
	if (map.doesThePlayerWantColors())
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
	cout << "Score:" << score+sumOfLastScores << "     Lives:" << livesLeft << endl;
	if (map.doesThePlayerWantColors())
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
}

Position Game::setFruitStartingPos()
{
	int fruitRandomX, fruitRandomY;
	
	bool goodPlace = false;
	do 
	{
		fruitRandomX = rand() % (map.getCols()-1);
		fruitRandomY = rand() % (map.getRows()-1);
		goodPlace = doesFruitFallOnEntities(Position(fruitRandomY, fruitRandomX));
		
	} while (map.getSymbolInMap(fruitRandomY, fruitRandomX) == WALL || map.getSymbolInMap(fruitRandomY, fruitRandomX) == TUNNEL || !goodPlace);
	Position pos = Position(fruitRandomY, fruitRandomX);
	return pos;
}

bool Game::doesFruitFallOnEntities(Position pos)
{
	bool allchecked = false;
	Fruit tempfruit(pos);
	while(!allchecked) {
		if (pacman == tempfruit) {
			break;
		}
		for (GhostBase* iterator : ghostArray)
		{
			if (tempfruit == *iterator)
				break;
		}
		allchecked = true;
	}
	return allchecked;
}

