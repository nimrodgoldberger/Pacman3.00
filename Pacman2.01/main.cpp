
#include "FilesList.h"

#define MAXLINE 30
//using namespace std;
/*MENU FUNCTIONS*/
void mainMenu(FilesList& list);/*Displays the Menu and acts according to the player's choice*/
void printMenu(int numOfFilesInDirectory);/*Prints the main menu */
char playCurrScreenGame(FilesList& list);


int main(int argc, char* argv[])
{
	
	FilesList lst;
	lst.getFilesFromDirectory();
	//lst.printListOfFiles();
	if (lst.getNumOfMaps()==0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
		cout << "ERROR,there are no legal screen files in the working directory!" << endl << "Please add the necessary files and try again.";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
	}
	else
	{
		mainMenu(lst);

	}
	return 0;
}



void mainMenu(FilesList& list)
{
	int numOfFilesInDirectory=list.getNumOfMaps();
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
			system("CLS");
			Game theGame = Game::Game(list.getListOfFiles()[0], startingScore);
			theGame.begin(startingScore);
			break;
		}
		case 2:
		{
			string fName;
			cout << "Please enter the correct File Name.(example: pacman_03.screen)" << endl;
			std::string path = ".";
			cin >> fName;
			size_t found = fName.find(".screen");
			while(found == string::npos)
			{
				cout << "Please enter the correct File Name." << endl;
				cin >> fName;
				found = fName.find(".screen"); 
			}
			int startingScore = 0;
			system("CLS");
			Game theGame = Game::Game(fName, startingScore);
			theGame.begin(startingScore);
			break;
		}
		case 3:
		{
			system("CLS");
			char c=playCurrScreenGame(list);
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
}
void printMenu(int numOfFilesInDirectory)
{
	cout << "(1) Start a new Game in a default Map" << endl;
	cout << "(2) Start a new Game using a specific file name" << endl;
	cout << "(3) Start the challenge of " << numOfFilesInDirectory << " boards" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

char playCurrScreenGame(FilesList& list)
{
	int sumOfScores = 0;
	bool didPlayerWin=true;
	
	vector<string> vs = list.getListOfFiles();
	Game* game;
	for (string s :vs)
	{
		game = new Game(s, sumOfScores);
		didPlayerWin= game->begin(sumOfScores);
		/*dtor!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		if (!didPlayerWin)
		{
			break;
		}
		else
		{
			if (s!=vs.back())
			{
				system("CLS");
				cout << "WELL DONE!!! YOUR CURRENT SCORE IS: " << sumOfScores << endl;
			}
			
		}
	}
	if (didPlayerWin)
	{
		system("CLS");
		cout<<"AMAZING YOU WON ALL THE LEVELS!!!!"<< endl << endl << "YOUR TOTAL SCORE IS: " << sumOfScores << endl;
	}
	else
	{
		system("CLS");
		cout<< "GAME OVER" << endl <<"Better luck next time.." << "   YOUR SCORE WAS: " << sumOfScores << endl;
	}
	return _getch();
}
 
