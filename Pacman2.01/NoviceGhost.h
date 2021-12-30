#pragma once
#include "GhostBase.h"
class NoviceGhost :
    public GhostBase
{
public:
    NoviceGhost() = default;
    NoviceGhost(Position startPos):GhostBase(startPos){}
    void setDirection(char newDirection);
    void decideGhostDirection(Map& mp, char** theMap, int yDest, int xDest);
    void randDirection();


};

