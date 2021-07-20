#include "Projectile.h"

void Projectile::setProj(unsigned long int mils, int x)
{
	this->x = x;
	orgTime = mils;
	isTrash = false;
	tempTrash = false;
}

void Projectile::Draw(LedControl & brd, int addr)
{
	if (tempTrash)
	{
		brd.setLed(addr, 0, x, false);
		isTrash = true;
	}
	else
	{
		brd.setLed(addr, y, x, true);
		if (y != 5)
		{
			for (int j = 5; j > y; j--)
			{
				brd.setLed(addr, j, x, false);
			}
		}
	}
}

void Projectile::Update(int speed)
{
	unsigned short int dt = (unsigned short int)(millis() - orgTime);
	if (dt <= (speed * 5 + 20))
	{
		unsigned short int step = (unsigned short int)(dt / speed);
		y = 5 - step;
	}
	else
	{
		tempTrash = true;
	}
}
