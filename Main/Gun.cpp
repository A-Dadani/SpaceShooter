#include "Gun.h"

void Gun::Draw(LedControl& brd, int addr) const
{
	brd.setRow(addr, 6, 0x00);
	brd.setRow(addr, 7, 0x00); //clearing the space for the gun so we don't draw 2 overlaping guns in case of movement 
	brd.setLed(addr, 7, x, true);
	brd.setLed(addr, 6, x, true);
	if (x != 0)
	{
		brd.setLed(addr, 7, x - 1, true);
	}
	if (x != 7)
	{
		brd.setLed(addr, 7, x + 1, true);
	}
}

void Gun::moveRight()
{
	if (x != 7)
	{
		++x;
	}
}

void Gun::moveLeft()
{
	if (x != 0)
	{
		--x;
	}
}
