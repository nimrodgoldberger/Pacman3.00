#pragma once

#include <queue>
#include "Entity.h"
#include "Map.h"  
#define MAX_ROUTE_LEN  2000
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
class GhostBase :public Entity
{
private:
	char symbol = '?';
public:
	GhostBase( Position startPos) : Entity( startPos) {}
	GhostBase() = default;
	virtual ~GhostBase(){};
	char move(Map & mp, int pacmanY, int pacmanX,bool colorful,int scoreAndLivesRow);
	virtual void setDirection(char newDirection)=0;
	void printSymbol()const { cout << symbol; };
    virtual void decideGhostDirection(Map& mp, char** theMap, int yDest, int xDest)=0;

    class QItem {
    public:
        int row;
        int col;
        int dist;
        QItem(int x, int y, int w) : row(x), col(y), dist(w) {}
    };
    int minDistance(Map& mp, char** theMap, int yD, int xD, int currY, int currX);
    char chooseDirectionFromShortRoute(int up, int down, int left, int right);
    virtual char type()const { return symbol; };

};

