#pragma once
#include "GhostBase.h"
#include "Map.h"
class GoodGhost :
    public GhostBase
{
public:
    GoodGhost() = default;
    GoodGhost(Position startPos) :GhostBase(startPos) {}
    void setDirection(char newDirection);
    void decideGhostDirection(Map& mp, char** theMap, int yDest,int xDest);
    void randDirection();
};

