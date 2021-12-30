#pragma once
//#include <windows.h>

//using namespace std;
#include "Map.h"
#include <string>
using std::string;

#include <iostream>
#include <process.h>
#include <conio.h>
#include <fstream>
#include "Position.h"
#define UP 'w'
#define DOWN 'x'	
#define LEFT 'a'
#define RIGHT 'd'
#define STAY 's'
//#include "Entity.h"
#include "Pacman.h"
#include "GhostBase.h"

#include "NoviceGhost.h"
#include "GoodGhost.h"
#include "BestGhost.h"
#include "Fruit.h"

/*Pressed for pausing the game or returning to the main menu from the instructions' page*/
#define ESC 27 
/*Different directions for the Entities' movement*/

enum class ghostType{Best,Good, Novice};

class Game
{
private:
	int sumOfLastScores = 0;
	int winningScore=0;
	ghostType difficultyLevel = ghostType::Novice;
	int score;/*The player's score*/
	int livesLeft;/*The number of lives left for the player*/
	Map map;/*The laberinth in which the game takes place*/
	Pacman pacman; /*This is the avatar of the player marked with: '@', the ctor puts it in it's starting position*/
	Fruit* fruit=nullptr;
	vector<GhostBase*> ghostArray;

public:

	/*CONSTRUCTORS*/
	Game(string fileName,int& sumOfScores);

	/*GETTERS*/
	int getLivesLeft()const;/*Returns the number of lives left*/
	int getScore()const;/*Returns the current score*/
	char getSymbol(int y, int x);/*Returns the type of object located at[y][x] int the Map*/
	char getKey(char c)const;/*recieves an input from the player for the direction, if the input is invalid, returns the player's last valid direction*/
	
	/*SETTERS*/
	void setScore();/*Increases the score by one*/
	void setNumOfLives();/*Decreases the nuber of lives by one*/
	/*Start the Game Functions*/
	bool begin(int& sumOfScores);/*Calls the ctor of the map, recieves the player's choice about playing in color or not,prints map and score\lives bar ,and calls the movePacMan*/
	/*Printing Functions*/
	void printScoreAndLives(int lineOfScoreBar);/*Goes to the bottom of the MAP and prints the updated score and lives count*/
	
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
	void askGhostLevel();
	bool startGame(int& sumOfScores);

	Position setFruitStartingPos();
	bool doesFruitFallOnEntities(Position pos);
};




