#include "GhostBase.h"

char GhostBase::move(Map& mp,int pacmanY, int pacmanX,bool colorful, int scoreAndLivesRow)
{
    decideGhostDirection(mp, mp.getMap(), pacmanY, pacmanX);
	char nextObject = mp.checkNextMove(y, x, entityDirection);
	switch (entityDirection)
	{
	case UP:
    {
        if (nextObject == TUNNEL || nextObject == WALL)
        {
            entityDirection = STAY;
        }
        else
        {
            if (scoreAndLivesRow==0)
                gotoxy(x, y+1);
            else
               gotoxy(x, y);
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
            cout << mp.getSymbolInMap(y, x);
            if (scoreAndLivesRow == 0)
                gotoxy(x, y);
            else
                gotoxy(x, y-1);
            setEntityYPos(y - 1);
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
               printSymbol();
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
        }
		break;
	}
	case DOWN:
	{
        if (nextObject == TUNNEL || nextObject == WALL)
        {
            entityDirection = STAY;
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
                gotoxy(x, y + 2);
            else
                gotoxy(x, y + 1);
			setEntityYPos(y + 1);
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
            printSymbol();
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
        
		break;
	}
	case LEFT:
	{
        if (nextObject == TUNNEL || nextObject == WALL)
        {
            entityDirection = STAY;
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
                gotoxy(x-1, y);
			setEntityXPos(x - 1);
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
            printSymbol();
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
        
		break;
	}
	case RIGHT:
	{
        if (nextObject == TUNNEL || nextObject == WALL)
        {
            entityDirection = STAY;
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
                gotoxy(x + 1, y + 1);
            else
                gotoxy(x + 1, y);
			setEntityXPos(x + 1);
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
            printSymbol();
            if (colorful)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (11));
		}
		break;
	}
	/*case STAY:
	{
        decideGhostDirection(mp, mp.getMap(), pacmanY, pacmanX);
        gotoxy(x, y);
        printSymbol();
		break;
	}*/
	}
    return entityDirection;
}

char GhostBase::chooseDirectionFromShortRoute(int up, int down, int left, int right)
{
    if (up <= down && up <= left && up <= right )
    {
        return UP;
    }
    else if (down <= up && down <= left && down <= right)
    {
        return DOWN;
    }
    else if (right <= up && right <= left && right <= down)
    {
        return RIGHT;
    }
    else
        return LEFT;
}

int GhostBase::minDistance(Map& mp, char** theMap, int yD, int xD,int currY,int currX)
{
    QItem source(0 ,0, 0);// To keep track of visited QItems. Marking blocked cells as visited.
    bool** visited;
    visited = new bool* [mp.getRows()];
    for (int j = 0; j < mp.getRows(); j++)
    {
        visited[j] = new bool[mp.getCols()];
    }
    for (int i = 0; i < mp.getRows(); i++) {
        for (int j = 0; j < mp.getCols(); j++)
        {
            switch (theMap[i][j])
            {
            case TUNNEL:
            case WALL:
            {
                visited[i][j] = true;
                break;
            }
            default:
            {
                visited[i][j] = false;
                break;
            }
            }
            if (j == currX && i == currY)
            {
                source.row = i;
                source.col = j;
            }
        }
    }
    // applying BFS on matrix cells starting from source
    queue<QItem>q;
    q.push(source);
    visited[source.row][source.col] = true;
    while (!q.empty()) {
        QItem p = q.front();
        q.pop();
        // Destination found;
        if (p.row == yD && p.col == xD)
            return p.dist;
        // moving up
        if (p.row - 1 >= 0 && visited[p.row - 1][p.col] == false)
        {
            q.push(QItem(p.row - 1, p.col, p.dist + 1));
            visited[p.row - 1][p.col] = true;
        }
        // moving down
        if (p.row + 1 < mp.getRows() && visited[p.row + 1][p.col] == false)
        {
            q.push(QItem(p.row + 1, p.col, p.dist + 1));
            visited[p.row + 1][p.col] = true;
        }
        // moving left
        if (p.col - 1 >= 0 && visited[p.row][p.col - 1] == false)
        {
            q.push(QItem(p.row, p.col - 1, p.dist + 1));
            visited[p.row][p.col - 1] = true;
        }
        // moving right
        if (p.col + 1 < mp.getCols() && visited[p.row][p.col + 1] == false)
        {
            q.push(QItem(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col + 1] = true;
        }
    }
    return -1;
}


