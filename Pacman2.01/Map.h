#pragma once
//#include "Game.h"
#include "Position.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;
/*Indicate if the game will be played in Color or in Black and White*/
#define BLACKANDWHITE false
#define COLORFUL true
#define WALL '#'
#define EMPTY '%'
#define CRUMB ' '
#define PACMAN '@'
#define GHOST '$'
#define FREE ' '
#define CRUMBSIGN '-'
#define GHOSTSIGN '?'
#define SCOREANDLIVES '&'
#define TUNNEL 'O'
#define UP 'w'
#define DOWN 'x'
#define LEFT 'a'
#define RIGHT 'd'
#define STAY 's'
enum class GameMode { load, loadSilent, simple, save };

//class Map
//{
//private:
//	bool inColor = true;/*The default will be to play with colours*/
//	Position TheMap[27][17];/*The map is a 2D array of Positions (class) and it is the Board in which we play*/
//public:
//	Map();/*The ctor of the map, creates it with all the crumbs, in its default settings*/
//	/*COLOR CHANGING FUNCTIONs*/
//	bool doesThePlayerWantColors();/*Returns true if the player wanted colors while playing*/
//	void setColorChoice();/*Asks the player if he wants colors while playing*/
//	/*functions*/
//	void printMap();/*Prints the map with the current values(if a crumb was eaten it will print it as a free, place)*/
//	typeOfObject getSymbolInMap(int y, int x);/*Returns the content of the map in[y][x]*/
//	void setSymbolInMap(int y, int x, typeOfObject newType);/*Changes the content of the map at [y][x]*/
//};
class Map
{
private:
	bool inColor = true;
	char** TheMap;
	int numOfCrumbs=0;
	int rows = 0;
	int cols = 0;
	int lineOfScoreBar = 0;
	bool isThereAsinglePacman = false;
	int countTunnels = 0;
	Position pacManStartingPos = Position();
	vector<Position> GhostArr;


public:
	Map(string fileName);/*The ctor of the map, creates it with all the crumbs, in its default settings*/
	
	/*COLOR CHANGING FUNCTIONs*/
	bool doesThePlayerWantColors();/*Returns true if the player wanted colors while playing*/
	void setColorChoice();/*Asks the player if he wants colors while playing*/
	/*functions*/
	void printMap();/*Prints the map with the current values(if a crumb was eaten it will print it as a free, place)*/
	char getSymbolInMap(int y, int x);/*Returns the content of the map in[y][x]*/
	void setSymbolInMap(int y, int x, char newType);/*Changes the content of the map at [y][x]*/
	char deCodeFile(char c);
	char checkNextMove(int y, int x, char direction);
	inline int getLineOfScoreBar() {return lineOfScoreBar;}
	inline int getRows() { return rows; };
	inline int getCols() { return cols;};
	Position getPacmanStartPos();
	Position getGhostStartPos(int index);
	inline int getNumOfCrumbs() { return numOfCrumbs; }
	inline vector<Position> getGhostArr() { return GhostArr; }
	char** getMap() { return TheMap; }
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

