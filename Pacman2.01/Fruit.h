#pragma once

#include "Entity.h"
class Fruit :
    public Entity
{
private:
    char symbol = '5';
    int lifeTime;
public:
    Fruit(Position startPos) : Entity(startPos) { setLifeTime(); setSymbol(); }
    Fruit() = default;
    virtual ~Fruit(){};

    void move(Map& mp, int pacmanY, int pacmanX,bool colorful, int scoreAndLivesRow);
    void setDirection(char newDirection);
    void randDirection();
    int getLifeTime()const;
    void setLifeTime();
    void setSymbol();
    void printSymbol()const { cout << symbol; } ;
    char type()const { return symbol; };
    void ZeroLifeTime();



};

