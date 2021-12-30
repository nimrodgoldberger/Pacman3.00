#pragma once

#include "GhostBase.h"
#include "Map.h"

class BestGhost :
    public GhostBase
{
public:
    BestGhost() = default;
    BestGhost(Position startPos) :GhostBase(startPos) {}
    void setDirection(char newDirection);/*changes ghost direction*/
    void decideGhostDirection(Map& mp, char** theMap, int yDest, int xDest);/*decides the direction of ghost depending on the pacman position*/
};

