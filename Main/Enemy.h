#pragma once
#include <LedControl.h>

class Enemy
{
public:
	void Spawn(unsigned long int time, int x);
	void Update(LedControl& brd, int addr, int speed, int enemySpeed);
	void Draw(LedControl& brd, int addr);
	void Erase(LedControl& brd, int addr);
	void shot(LedControl& brd, int addr, unsigned long int timeOfDeath);
	int getX() const { return x; }
	unsigned long int getTimeOfDeath() const { return timeOfDeath; }
public:
	bool isGameOver = false;
	bool isErased = true;
private:
	bool isShot = false;
	unsigned long int timeOfDeath = 0;
	unsigned long int orgTime;
	int x;
	int y = -1;
};