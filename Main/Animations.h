#pragma once
#include "Letters.h"
#include <LedControl.h>

namespace Animations
{
	void start(LedControl& brd, int addr)
	{
		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0xFF);
		}
		delay(100);
		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0x00);
		}
		delay(100);
		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0xFF);
		}
		delay(100);
		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0x00);
		}
		delay(100);
	}

	void gameOver(LedControl& brd, int addr, int intensity)
	{

		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0xFF);
			delay(60);
		}
		for (int i = 0; i < 8; i++)
		{
			brd.setRow(addr, i, 0x00);
			delay(60);
		}
		delay(500);
		Letters::printLetter(brd, addr, Letters::frown);
		while (true)
		{
			brd.setIntensity(addr, 1);
			delay(500);
			brd.setIntensity(addr, intensity);
			delay(500);
		}
	}
}