#pragma once
#include <LedControl.h>

class Gun
{
public:
	void Draw(LedControl& brd, int addr) const;
	void moveRight();
	void moveLeft();
	int getX() const { return x; }
public:
	int x = 5;
};
