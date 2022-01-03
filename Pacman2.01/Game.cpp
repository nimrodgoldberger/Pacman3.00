#include "Game.h"

/*CONSTRUCTOR*/
Game::Game(string fileName, int& sumOfScores, int& sumoflives) :map(Map(fileName))
{
	sumOfLastScores = sumOfScores;
	score = 0;
	livesLeft = sumoflives;
	winningScore = map.getNumOfCrumbs();
	pacman.setStartingPos(map.getPacmanStartPos());
}
/*FUNCTIONS*/
bool Game::startGame(int& sumOfScores, int& sumoflives, string stepsFileName, string resultsFileName, GameMode gameMode)
{
	bool GameOn = true, gameResult = true, isGamePaused = false, moveGhost = true, collision = false;
	char temp = 0;
	int fruitCoolDown = 0;
	char direction;
	int ghostNum;
	ofstream StepFileW, ResultFileW;
	ifstream StepFileR, ResultFileR;
	if (gameMode == GameMode::save)
	{
		StepFileW = ofstream(stepsFileName, ios_base::out | std::ofstream::trunc);
		ResultFileW = ofstream(resultsFileName, ios_base::out | std::ofstream::trunc);
	}
	else if (gameMode != GameMode::simple)
	{
		StepFileR = ifstream(stepsFileName, ios_base::in);
		ResultFileR = ifstream(resultsFileName, ios_base::in);
	}
	switch (gameMode)
	{
	case GameMode::load:
	case GameMode::loadSilent:
	{
		PairsOfResult stepsCountForTest;
		//to do
		vector<PairsOfResult> theResults;
		PairsOfResult temp;
		int steps = 0;
		stepsCountForTest.timeOfEvent = 0;
		char entity;
		int fruitValue;
		int fruitY;
		int fruitX;
		int ghostNumber;
		char direct;
		char directG;
		char directP;
		bool color = true;
		while (!ResultFileR.eof())
		{
			ResultFileR >> temp.event >> temp.timeOfEvent;
			theResults.push_back(temp);
		}
		for (int i = 0; i < theResults.size(); i++)
		{
			

			while (steps < theResults[i].timeOfEvent)
			{
				StepFileR >> entity;
				switch (entity)
				{
				case 'f'://fruit
				{
					StepFileR >> direct;
					switch (direct)
					{
					case 'B':
					{
						StepFileR >> fruitValue;
						StepFileR >> fruitY;
						StepFileR >> fruitX;
						fruit = new Fruit(Position(fruitY, fruitX));
						fruit->setSymbol(fruitValue);
						break;
					}
					case 'e':
					{
						winningScore += (fruit->type() - '0');//maybe unnecessary
						score += (fruit->type() - '0');
						delete[] fruit;
						fruit = nullptr;
						if (gameMode != GameMode::loadSilent)
						{
							printScoreAndLives(map.getLineOfScoreBar());
						}

						break;
					}
					case 'E':
					{
						if (gameMode != GameMode::loadSilent)
						{
							if (map.getLineOfScoreBar() == 0)
								gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos() + 1);
							else
								gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos());
							if (map.doesThePlayerWantColors())
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
							cout << map.getSymbolInMap(fruit->getEntityYPos(), fruit->getEntityXPos());
						}
						delete[] fruit;
						fruit = nullptr;
						break;
					}
					case 'w':
					case 'a':
					case 's':
					case 'd':
					case 'x':
					{
						fruit->move_load(direct, 'f', map, color, map.getLineOfScoreBar(), gameMode);
						break;
					}
					default:
						cout << "ERROR ERROR";
						exit(1);
					}
					break;
				}
				case 'p'://pacman
				{
					StepFileR >> direct;
					directP = direct;
					pacman.move_load(direct, 'p', map, color, map.getLineOfScoreBar(), gameMode);
					if (gameMode == GameMode::loadSilent)
						stepsCountForTest.timeOfEvent++;
					steps++;
					if (getSymbol(pacman.getEntityYPos(), pacman.getEntityXPos()) == CRUMBSIGN)
					{
						map.setSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos(), FREE);
						score++;
						if (gameMode != GameMode::loadSilent)
						{
							printScoreAndLives(map.getLineOfScoreBar());
						}
					}
					break;
				}
				case 'g'://ghost
				{
					StepFileR >> ghostNumber;
					StepFileR >> direct;
					directG = direct;
					ghostArray[ghostNumber]->move_load(direct, 'g', map, color, map.getLineOfScoreBar(), gameMode);
					break;
				}
				default:
					cout << "NO SUCH ENTITY TYPE";
					exit(1);
				}
				if (gameMode != GameMode::loadSilent)
				Sleep(50);
				
			}

			if (gameMode == GameMode::loadSilent)
			{
				for (GhostBase* iterator : ghostArray)
				{
					switch (directP)
					{
					case 'w':
					{
						if (pacman.getEntityXPos() - 1 == iterator->getEntityXPos() && pacman.getEntityYPos() == iterator->getEntityYPos())
						{
							stepsCountForTest.event = 'D';
							break;
						}
						else
							stepsCountForTest.event = 'W';
						break;
					}
					case 'x':
					{
						if (pacman.getEntityXPos() + 1 == iterator->getEntityXPos() && pacman.getEntityYPos() == iterator->getEntityYPos())
						{
							stepsCountForTest.event = 'D';
							break;
						}
						else
							stepsCountForTest.event = 'W';
						break;
					}
					case 'a':
					{
						if (pacman.getEntityXPos() == iterator->getEntityXPos() && pacman.getEntityYPos() - 1 == iterator->getEntityYPos())
						{
							stepsCountForTest.event = 'D';
							break;
						}
						else
							stepsCountForTest.event = 'W';
						break;
					}
					case 'd':
					{
						if (pacman.getEntityXPos() == iterator->getEntityXPos() && pacman.getEntityYPos() + 1 == iterator->getEntityYPos())
						{
							stepsCountForTest.event = 'D';
							break;
						}
						else
							stepsCountForTest.event = 'W';
						break;
					}
					case 's':
					{
						switch (directG)
						{
						case 'w':
						{
							if (pacman.getEntityXPos() == iterator->getEntityXPos() - 1 && pacman.getEntityYPos() == iterator->getEntityYPos())
							{
								stepsCountForTest.event = 'D';
								break;
							}
							else
								stepsCountForTest.event = 'W';
							break;
						}
						case 'x':
						{
							if (pacman.getEntityXPos() == iterator->getEntityXPos() + 1 && pacman.getEntityYPos() == iterator->getEntityYPos())
							{
								stepsCountForTest.event = 'D';
								break;
							}
							else
								stepsCountForTest.event = 'W';
							break;
						}
						case 'a':
						{
							if (pacman.getEntityXPos() == iterator->getEntityXPos() && pacman.getEntityYPos() == iterator->getEntityYPos() - 1)
							{
								stepsCountForTest.event = 'D';
								break;
							}
							else
								stepsCountForTest.event = 'W';
							break;
						}
						case 'd':
						{
							if (pacman.getEntityXPos() == iterator->getEntityXPos() && pacman.getEntityYPos() == iterator->getEntityYPos() + 1)
							{
								stepsCountForTest.event = 'D';
								break;
							}
							else
								stepsCountForTest.event = 'W';
							break;
						}
						default:
							cout << "ERROR NUMBER -1";
							gameResult = false;
							break;
						}
						break;
					}
					default:
						break;
					}
					/*if (pacman.getEntityXPos()==iterator->getEntityXPos() && pacman.getEntityYPos() == iterator->getEntityYPos())
					{
						stepsCountForTest.event = 'D';
						break;
					}
					else
					stepsCountForTest.event = 'W';*/

				}
				if (theResults[i].event == 'D' && stepsCountForTest.event == 'D')
				{
					if (stepsCountForTest.timeOfEvent!=theResults[i].timeOfEvent)
					{
						gameResult = false;
					
						//error!!!!!
						cout << "ERROR NUMBER 0";
					}
				}
				else if (theResults[i].event == 'W' && stepsCountForTest.event == 'W')
				{
					if (stepsCountForTest.timeOfEvent != theResults[i].timeOfEvent)
					{
						//good
						gameResult = false;
						cout << "ERROR NUMBER 1";
						//error!!!!!
					}
				}
				else
				{
					gameResult = false;
					cout << "ERROR NUMBER 2";
					//ERROR!!!!!!!!!!
				}

			}
			if (theResults[i].event == 'D')
			{
				livesLeft--;
				if (gameMode != GameMode::loadSilent)
				{
					if (map.getLineOfScoreBar() == 0)
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos() + 1);
					else
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					//***************************************
					cout << map.getSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos());
				}
				pacman.setEntityYPos(pacman.getStartingPos().getY());
				pacman.setEntityXPos(pacman.getStartingPos().getX());
				if (gameMode != GameMode::loadSilent)
				{
					if (map.getLineOfScoreBar() == 0)
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos() + 1);
					else
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					pacman.printSymbol();
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					printScoreAndLives(map.getLineOfScoreBar());
				}
				for (GhostBase* iterator : ghostArray)
				{
					if (gameMode != GameMode::loadSilent)
					{
						if (map.getLineOfScoreBar() == 0)
							gotoxy(iterator->getEntityXPos(), iterator->getEntityYPos() + 1);
						else
							gotoxy(iterator->getEntityXPos(), iterator->getEntityYPos());
						if (map.doesThePlayerWantColors())
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
						cout << map.getSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos());
						if (map.doesThePlayerWantColors())
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					}
					iterator->setEntityYPos(iterator->getStartingPos().getY());
					iterator->setEntityXPos(iterator->getStartingPos().getX());
					if (gameMode != GameMode::loadSilent)
					{
						if (map.getLineOfScoreBar() == 0)
							gotoxy(iterator->getEntityXPos(), iterator->getEntityYPos() + 1);
						else
							gotoxy(iterator->getEntityXPos(), iterator->getEntityYPos());
						if (map.doesThePlayerWantColors())
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
						iterator->printSymbol();
						if (map.doesThePlayerWantColors())
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
					}
					break;
				}//put everyone back at their starting places
			}
			//else
			//{
			//	//print win set lives and set total score
			//	//go to the next screen 
			//	//return true;
			//}
		}

		//print lost message and exit;
		//return false;
		StepFileR.close();
		ResultFileR.close();
		break;
	}
	case GameMode::simple:
	case GameMode::save:
	{
		while (GameOn)
		{
			while (!isGamePaused)
			{
				while (!_kbhit() && livesLeft > 0 && score < winningScore && !collision && fruitCoolDown>0)
				{
					ghostNum = 0;
					if (getSymbol(pacman.getEntityYPos(), pacman.getEntityXPos()) == CRUMBSIGN)
					{
						map.setSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos(), FREE);
						score++;
						printScoreAndLives(map.getLineOfScoreBar());
					}

					direction = pacman.move(map, pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(), map.getLineOfScoreBar());
					countSteps++;

					if (fruit != nullptr)
					{
						if (*fruit == pacman)
						{
							if (gameMode == GameMode::save)
							{
								StepFileW << 'f' << 'e';//Fruit eaten by pacman
							}
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
							if (gameMode == GameMode::save)
							{
								ResultFileW << 'D' << countSteps;//Pacman Dead
								//StepFileW << 'g' << ghostNum << 's';
							}
							collision = true;
							break;
						}

					}
					if (gameMode == GameMode::save)
					{
						if (collision)
						{
							StepFileW << 'p' << 's';

						}
						else
							StepFileW << 'p' << direction;
					}
					if (collision)
						break;
					if (moveGhost)
					{
						if (fruit != nullptr)
						{

							direction = fruit->move(map, pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(), map.getLineOfScoreBar());
							if (gameMode == GameMode::save)
							{
								StepFileW << 'f' << direction;
							}

							if (*fruit == pacman)
							{
								if (gameMode == GameMode::save)
								{
									StepFileW << 'f' << 'e';//Fruit eaten by pacman
								}
								winningScore += (fruit->type() - '0');
								score += (fruit->type() - '0');
								if (map.getLineOfScoreBar() == 0)
									gotoxy(fruit->getEntityXPos(), fruit->getEntityYPos() + 1);
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
									if (gameMode == GameMode::save)
									{
										StepFileW << 'f' << 'E';//Fruit Eaten by ghost
									}
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
							/*if (collision)
							{
								direction = 's';
							/*}*/
							//else*/
								direction = (*iterator).move(map, pacman.getEntityYPos(), pacman.getEntityXPos(), map.doesThePlayerWantColors(), map.getLineOfScoreBar());

							/*if (gameMode == GameMode::save)
							{
								StepFileW << 'g' << ghostNum << direction;
							}*/
							/*
							if (*iterator == pacman)
							{
								if (gameMode == GameMode::save && !collision)
								{
									//alll ghosts left to stay

									StepFileW << 'g' << ghostNum << 's';

									ResultFileW << 'D' << countSteps;//Pacman Dead

								}
								collision = true;
								//StepFileW << 'g' << ghostNum << 's';//MAYBE INSTEAD OF TWO MOVES, ONLY THIS
								break;
							}
							else
							{
								if (gameMode == GameMode::save)
								{
									StepFileW << 'g' << ghostNum << direction;

								}
							}
							*/
							if (*iterator == pacman && !collision)
							{
								if (gameMode == GameMode::save && !collision)
								{
									ResultFileW << 'D' << countSteps;//Pacman Dead
								}
								collision = true;
								//StepFileW << 'g' << ghostNum << 's';//MAYBE INSTEAD OF TWO MOVES, ONLY THIS
								//break;
							}
							if (collision)
							{
								direction = 's';
							}
							if (gameMode == GameMode::save)
							{
								StepFileW << 'g' << ghostNum << direction;
							}
							if (fruit != nullptr)
							{
								if (*iterator == *fruit)
								{
									if (gameMode == GameMode::save)
									{
										StepFileW << 'f' << 'E';//Fruit Eaten by ghost
									}
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
							ghostNum++;
						}
						//if (collision)
							//break;
						moveGhost = false;
						fruitCoolDown--;
					}
					else
						moveGhost = true;

					if (fruit != nullptr)
					{
						if (fruit->getLifeTime() == 0)
						{
							if (gameMode == GameMode::save)
							{
								StepFileW << 'f' << 'E';//Fruit Eaten by ghost
							}
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

					Sleep(100);
				}
				if (fruitCoolDown == 0)
				{
					fruit = new Fruit(setFruitStartingPos());
					if (gameMode == GameMode::save)
					{
						StepFileW << 'f' << 'B' << (fruit->type() - '0') << ' ' << fruit->getEntityYPos() << ' ' << fruit->getEntityXPos();//Fruit Born by pacman
					}
					fruitCoolDown = fruit->getLifeTime() + (rand() % 20) + 30;
				}
				if (collision)
				{
					/*if (gameMode == GameMode::save) {
						StepFileW << 'p' << 's';
					}*/
					setNumOfLives();
					printScoreAndLives(map.getLineOfScoreBar());
					if (map.getLineOfScoreBar() == 0)
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos() + 1);
					else
						gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
					cout << map.getSymbolInMap(pacman.getEntityYPos(), pacman.getEntityXPos());
					pacman.setDirection(STAY);
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

					ghostNum = 0;
					for (GhostBase* iterator : ghostArray)
					{
						/*if (gameMode == GameMode::save) {
							StepFileW << 'g' << ghostNum << 's';
						}*/
						if (map.getLineOfScoreBar() == 0)
							gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos() + 1);
						else
							gotoxy((*iterator).getEntityXPos(), (*iterator).getEntityYPos());
						cout << map.getSymbolInMap((*iterator).getEntityYPos(), (*iterator).getEntityXPos());
						(*iterator).setDirection(STAY);
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

						ghostNum++;
					}
					collision = false;
				}

				if (livesLeft == 0)/*LOST*/
				{
					//if (gameMode == GameMode::save)
					//{
					//	ResultFileW << 'D' << countSteps;//Pacman Dead
					//}
					system("CLS");
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					cout << "YOU LOST..." << endl << "YOUR SCORE WAS: " << score << endl;
					GameOn = false;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
					break;
				}
				else if (score == winningScore)/*WON*/
				{
					if (gameMode == GameMode::save)
					{
						ResultFileW << 'W' << countSteps;//Pacman Dead
					}
					system("CLS");
					if (map.doesThePlayerWantColors())
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
					cout << "YOU WON!! CONGRATS!" << endl << "YOUR SCORE IS: " << score << endl;
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
				cout << endl << " The game is Paused." << endl << "Press ESC continue";
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
		if (gameMode != GameMode::simple)
		{
			StepFileW.close();
			ResultFileW.close();
		}
		break;
	}//case save or simple closer
	}//switch closer
	sumOfScores += score;
	if (gameMode == GameMode::loadSilent)
	{
		return gameResult;
	}
	else
	{
		if (livesLeft == 0)
		{
			return false;
		}
		else
		{
			sumoflives = livesLeft;
			return true;
		}
	}
	

}


bool Game::begin(int& sumOfScores, int& sumoflives, string stepsFileName, string resultsFileName, GameMode gameMode)
{
	Sleep(1000);
	system("CLS");
	if (gameMode != GameMode::load && gameMode != GameMode::loadSilent)
	{
		askGhostLevel();
		map.setColorChoice();
	}
	if (gameMode != GameMode::loadSilent)
	{
		map.printMap();
		if (map.getLineOfScoreBar() == 0)
			gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos() + 1);
		else
			gotoxy(pacman.getEntityXPos(), pacman.getEntityYPos());
		if (map.doesThePlayerWantColors())
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
		pacman.printSymbol();
		if (map.doesThePlayerWantColors())
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		printScoreAndLives(map.getLineOfScoreBar());
	}
	for (int i = 0; i < map.getGhostArr().size(); i++)
	{
		if (difficultyLevel == ghostType::Novice)
		{
			NoviceGhost* casper = new NoviceGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (gameMode != GameMode::loadSilent)
			{
				if (map.getLineOfScoreBar() == 0)
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY() + 1);
				else
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				(*casper).printSymbol();

			}
		}
		if (difficultyLevel == ghostType::Good)
		{
			GoodGhost* casper = new GoodGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (gameMode != GameMode::loadSilent)
			{
				if (map.getLineOfScoreBar() == 0)
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY() + 1);
				else
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				(*casper).printSymbol();
			}

		}
		if (difficultyLevel == ghostType::Best)
		{
			BestGhost* casper = new BestGhost(map.getGhostStartPos(i));
			ghostArray.push_back(casper);
			if (gameMode != GameMode::loadSilent)
			{
				if (map.getLineOfScoreBar() == 0)
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY() + 1);
				else
					gotoxy(map.getGhostArr()[i].getX(), map.getGhostArr()[i].getY());
				if (map.doesThePlayerWantColors())
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
				(*casper).printSymbol();
			}

		}
	}
	bool result = startGame(sumOfScores, sumoflives, stepsFileName, resultsFileName, gameMode);//maybe const
	if (gameMode == GameMode::loadSilent)
	{
		if (result)
			cout << "The test was successfull!!! Hurray";
		else
			cout << "The test has failed the run didn't go as planned...";
	}
	return result;
}

void Game::askGhostLevel()
{
	char levelChoice = 't';
	system("CLS");
	cout << "Choose Difficulty Level: " << endl << "For Novice press 1" << endl << "For Normal press 2" << endl << "For Hard press 3" << endl;
	while (levelChoice != '1' && levelChoice != '2' && levelChoice != '3')
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
	cout << "Score:" << score + sumOfLastScores << "     Lives:" << livesLeft << endl;
	if (map.doesThePlayerWantColors())
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
}

Position Game::setFruitStartingPos()
{
	int fruitRandomX, fruitRandomY;

	bool goodPlace = false;
	do
	{
		fruitRandomX = rand() % (map.getCols() - 1);
		fruitRandomY = rand() % (map.getRows() - 1);
		goodPlace = doesFruitFallOnEntities(Position(fruitRandomY, fruitRandomX));

	} while (map.getSymbolInMap(fruitRandomY, fruitRandomX) == WALL || map.getSymbolInMap(fruitRandomY, fruitRandomX) == TUNNEL || !goodPlace);
	Position pos = Position(fruitRandomY, fruitRandomX);
	return pos;
}

bool Game::doesFruitFallOnEntities(Position pos)
{
	bool allchecked = false;
	Fruit tempfruit(pos);
	while (!allchecked) {
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

