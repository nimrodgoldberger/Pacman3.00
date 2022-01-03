
#include "FilesList.h"

#define MAXLINE 30
//using namespace std;
/*MENU FUNCTIONS*/

void mainMenu(FilesList& screenlist, FilesList& stepslist, FilesList& resultslist, GameMode gameMode);/*Displays the Menu and acts according to the player's choice*/
void printMenu(int numOfFilesInDirectory);/*Prints the main menu */
char playCurrScreenGame(FilesList& screenlist, FilesList& stepslist, FilesList& resultslist, GameMode gameMode);


//int main(int argc, char** argv) {
//	InputParser input(argc, argv);
//	if (input.cmdOptionExists("-load")) {
//		cout <<"load"<<endl;
//	}
//	if (input.cmdOptionExists("-save")) {
//		cout << "save"<<endl;
//	}
//	if (input.cmdOptionExists("-silent")) {
//		cout << "silent" << endl;
//	}
//	/*const std::string& filename = input.getCmdOption("-f");*/
//	//if (!filename.empty()) {
//	//	// Do interesting things ...
//	//	cout << "nononoooo";
//
//	//}
//	return 0;
//}

//int main(int argc, char* argv[])
//{
//	InputParser input(argc, argv);
//	string s = "pacman_01.steps";
//	ifstream resFile(s, ios_base::in);
//	char c;
//	int num;
//	resFile >> c;
//	resFile >> c;
//	resFile >> num;
//	resFile >> num;
//	cout << num;
//	//	FilesList screenlst, stepslst, resultslst;
//	//	screenlst.getFilesFromDirectory(FileType::screen);
//}

int main(int argc, char* argv[])
{

	//if (input.cmdOptionExists("-silent")) {
	//	cout << "silent" << endl;
	//	if (argv[0]=="-load"&&argv[1]=="-silent")
	//	{
	//
	//	}
	//}
	InputParser input(argc, argv);
	FilesList screenlst, stepslst, resultslst;
	screenlst.getFilesFromDirectory(FileType::screen);
	//lst.printListOfFiles();

	if (screenlst.getNumOfMaps() == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
		cout << "ERROR,there are no legal screen files in the working directory!" << endl << "Please add the necessary files and try again.";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
	}
	else
	{
		screenlst.makeSureFilesAreThere(stepslst, FileType::steps, input);
		screenlst.makeSureFilesAreThere(resultslst, FileType::results, input);
		if (input.cmdOptionExists("-load")) {
			//cout << "load" << endl;
			if (input.cmdOptionExists("-silent"))
			{
				mainMenu(screenlst, stepslst, resultslst, GameMode::loadSilent);
				//cout << "silent" << endl;
			}
			else
			{
				mainMenu(screenlst, stepslst, resultslst, GameMode::load);
			}
		}
		if (input.cmdOptionExists("-save")) {
			mainMenu(screenlst, stepslst, resultslst, GameMode::save);
			//cout << "save" << endl;
		}
		else if (input.cmdOptionExists("-simple") || argc == 0)
		{
			mainMenu(screenlst, stepslst, resultslst, GameMode::simple);

		}

	}
	return 0;
}



void mainMenu(FilesList& screenlist, FilesList& stepslist, FilesList& resultslist, GameMode gameMode)
{
	char c = '_';
	switch (gameMode)
	{
	case GameMode::load:
		c = playCurrScreenGame(screenlist, stepslist, resultslist, gameMode);
		break;
	case GameMode::loadSilent:
		c = playCurrScreenGame(screenlist, stepslist, resultslist, gameMode);
		break;
	case GameMode::simple:
	case GameMode::save:
		int numOfFilesInDirectory = screenlist.getNumOfMaps();
		int response;
		char goBackToMainMenu = 'N';
		bool wantToPlay = true;
		while (wantToPlay == true)
		{
			printMenu(numOfFilesInDirectory);
			cin >> response;
			switch (response)
			{
			case 1:
			{
				int startingScore = 0;
				int sumoflives = 3;
				system("CLS");
				Game theGame = Game::Game(screenlist.getListOfFiles()[0], startingScore, sumoflives);
				theGame.begin(startingScore, sumoflives, stepslist.getListOfFiles()[0], resultslist.getListOfFiles()[0], gameMode);
				break;
			}
			case 2:
			{
				string fName;
				cout << "Please enter the correct File Name.(example: pacman_03.screen)" << endl;
				std::string path = ".";
				cin >> fName;
				size_t found = fName.find(".screen");
				while (found == string::npos)
				{
					cout << "Please enter the correct File Name." << endl;
					cin >> fName;
					found = fName.find(".screen");
				}
				int startingScore = 0;
				int sumoflives = 3;
				system("CLS");
				Game theGame = Game::Game(fName, startingScore, sumoflives);
				theGame.begin(startingScore, sumoflives, stepslist.getListOfFiles()[0], resultslist.getListOfFiles()[0], gameMode);
				break;
			}
			case 3:
			{
				system("CLS");
				c = playCurrScreenGame(screenlist, stepslist, resultslist, gameMode);
				system("CLS");
				break;
			}
			case 8:
			{
				system("CLS");
				cout << "Keys:" << endl << "LEFT: a or A" << endl << "RIGHT: d or D" << endl << "UP: w or W" << endl << "Down: x or X" << endl << "STAY: s or S" << endl;
				cout << "Your goal is to eat all the bread crumbs('-') while avoiding the ghosts('?')" << endl;
				cout << "You have a total of three lives and you lose one each time a ghost touches you" << endl;
				cout << "Please press ESC to go back to the MENU";
				while (goBackToMainMenu != ESC)
				{
					goBackToMainMenu = _getch();

				}
				goBackToMainMenu = 'N';
				system("CLS");
				break;
			}
			case 9:
			{
				system("CLS");
				cout << "Thank you for playing, goodbye!";
				wantToPlay = false;
				break;
			}
			default:
				system("CLS");
				cout << "Please choose a valid option";
				break;
			}
		}
		break;
	}

}
void printMenu(int numOfFilesInDirectory)
{
	cout << "(1) Start a new Game in a default Map" << endl;
	cout << "(2) Start a new Game using a specific file name" << endl;
	cout << "(3) Start the challenge of " << numOfFilesInDirectory << " boards" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

char playCurrScreenGame(FilesList& screenlist, FilesList& stepslist, FilesList& resultslist, GameMode gameMode)
{
	int sumOfScores = 0;
	int sumoflives = 3;
	bool didPlayerWin = true;
	vector<string> screensFnames = screenlist.getListOfFiles();
	vector<string> stepFnames = stepslist.getListOfFiles();
	vector<string> resultFnames = resultslist.getListOfFiles();

	Game* game;
	int numOfScreen = 0;
	for (string screen : screensFnames)
	{
		game = new Game(screen, sumOfScores, sumoflives);
		didPlayerWin = game->begin(sumOfScores, sumoflives, stepFnames[numOfScreen], resultFnames[numOfScreen], gameMode);
		numOfScreen++;
		/*dtor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		if (gameMode != GameMode::loadSilent)
		{
			if (!didPlayerWin)
			{
				break;
			}
			else
			{
				if (screen != screensFnames.back())
				{
					system("CLS");
					cout << "WELL DONE!!! YOUR CURRENT SCORE IS: " << sumOfScores << endl;
				}
			}
		}
	}
	if (gameMode != GameMode::loadSilent)
	{
		if (didPlayerWin)
		{
			system("CLS");
			cout << "AMAZING YOU WON ALL THE LEVELS!!!!" << endl << endl << "YOUR TOTAL SCORE IS: " << sumOfScores << endl;
		}
		else
		{
			system("CLS");
			cout << "GAME OVER" << endl << "Better luck next time.." << "   YOUR SCORE WAS: " << sumOfScores << endl;
		}
	}

	return _getch();
}

