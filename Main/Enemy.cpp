#include "Enemy.h"

void Enemy::Spawn(unsigned long int time, int x)
{
	orgTime = time;
	this->x = x;
	isErased = false;
	isShot = false;
}

void Enemy::Update(LedControl& brd, int addr, int speed, int enemySpeed)
{
	if (isShot && !isErased && ((millis() - timeOfDeath) > speed * (5 - y)))
	{
		Erase(brd, addr);
		isErased = true;
	}
	else
	{
		unsigned short int dt = (unsigned short int)(millis() - orgTime);
		if (dt <= 6 * enemySpeed)
		{
			unsigned short int step = (unsigned short int)(dt / enemySpeed);
			y = step - 1;
		}
		else if (dt > 6 * enemySpeed)
		{
			isGameOver = true;
		}
	}
}

void Enemy::Draw(LedControl& brd, int addr)
{
	if (y >= 0)
	{
		brd.setLed(addr, y, x, true);
		brd.setLed(addr, y, x + 1, true);
	}
	brd.setLed(addr, y + 1, x, true);
	brd.setLed(addr, y + 1, x + 1, true);
	if (y > 0)
	{
		brd.setLed(addr, y - 1, x, false);
		brd.setLed(addr, y - 1, x + 1, false);
	}
}

void Enemy::shot(LedControl& brd, int addr, unsigned long int timeOfDeath)
{
	isShot = true;
	this->timeOfDeath = timeOfDeath;
}

void Enemy::Erase(LedControl& brd, int addr)
{
	brd.setLed(addr, y, x, false);
	brd.setLed(addr, y + 1, x, false);
	brd.setLed(addr, y, x + 1, false);
	brd.setLed(addr, y + 1, x + 1, false);
	isErased = true;
}