#pragma once

class Position
{
private:
	int y=0;
	int x=0;
public:
	Position() = default;
	Position(int newY, int newX) : y(newY), x(newX) {};
	inline void setX(int newX) { x = newX; }
	inline void setY(int newY) { y = newY; }
	inline int getX()const { return x; }
	inline int getY()const { return y; }
	Position operator=(Position& newPos);
};

