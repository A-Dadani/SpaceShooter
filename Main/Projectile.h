#pragma once
#include <LedControl.h>

class Projectile
{
public:
	void setProj(unsigned long int mils, int x);
	void Draw(LedControl& brd, int addr);
	void Update(int speed);
public:
	bool getTrash() { return isTrash; }
private:
	bool isTrash = true;
	unsigned long int orgTime;
	int x;
	int y = 5;
	bool tempTrash = false;
};