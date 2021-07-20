#include "Gun.h"
#include "Projectile.h"
#include "Vector.h"
#include "Enemy.h"
#include "Animations.h"
#include <LedControl.h>

#define DIN 51
#define CS  53
#define CLK 52
#define ADDR 0
#define _BRD_INTENSITY 5
#define _SHOOT_BTN 2
#define _LEFT_BTN 3
#define _RIGHT_BTN 4
#define _PROJECTILE_SPEED_MS 30 //time projectile takes in one pixel
#define _ENEMY_SPEED_MS 600

void Update();
void Draw();

LedControl brd(DIN, CLK, CS, ADDR);
Gun gun;
Projectile prjctl;
Enemy enemies[7];

int eStep = 0;
bool isRight = false;
bool isLeft = false;
bool isShooting = false;
bool gameOver = false;

void setup()
{
	brd.shutdown(ADDR, false);
	brd.setIntensity(ADDR, _BRD_INTENSITY);
	brd.clearDisplay(ADDR);
	pinMode(_SHOOT_BTN, INPUT);
	pinMode(_LEFT_BTN, INPUT);
	pinMode(_RIGHT_BTN, INPUT);
	Animations::start(brd, ADDR);
}

void loop()
{
	if (gameOver)
	{
		Animations::gameOver(brd, ADDR, _BRD_INTENSITY);
	}
	else
	{
		Update();
	}

	if (!gameOver)
	{
		Draw();
	}
}

void Update()
{
	eStep = (millis() / 2000) % 7;
	if (enemies[eStep].isErased && (enemies[eStep].getTimeOfDeath() != 0 || (millis() - enemies[eStep].getTimeOfDeath()) <= 4000 ))
	{
		enemies[eStep].Spawn(millis(), micros() % 7);
	}

	bool OldRight = isRight;
	bool OldShooting = isShooting;
	bool OldLeft = isLeft;
	isShooting = (digitalRead(_SHOOT_BTN) == HIGH);
	isRight = (digitalRead(_RIGHT_BTN) == HIGH);
	isLeft = (digitalRead(_LEFT_BTN) == HIGH);

	if (!(isRight && isLeft)) //if both directions are pressed don't move
	{
		if (OldRight != isRight && isRight)
		{
			gun.moveRight();
		}
		else if (OldLeft != isLeft && isLeft)
		{
			gun.moveLeft();
		}
	}

	if (OldShooting != isShooting && isShooting && prjctl.getTrash()) //what game will do if shooting is detected
	{
		prjctl.setProj(millis(), gun.getX());
		for (auto& e : enemies)
		{
			if (e.getX() == gun.getX() || e.getX() + 1 == gun.getX())
			{
				e.shot(brd, ADDR, millis());
			}
		}
	}

	if (!prjctl.getTrash())
	{
		prjctl.Update(_PROJECTILE_SPEED_MS);
	}
	
	for (auto& e : enemies)
	{
		if (!e.isErased) // still need to implement e.gameover!!!!!
		{
			if (e.isGameOver)
			{
				gameOver = true;
				break;
			}
			e.Update(brd, ADDR, _PROJECTILE_SPEED_MS, _ENEMY_SPEED_MS);
		}
	}
}

void Draw()
{
	gun.Draw(brd, ADDR);
	if (!prjctl.getTrash())
	{
		prjctl.Draw(brd, ADDR);
	}
	for (auto& e : enemies)
	{
		if (!e.isErased)
		{
			e.Draw(brd, ADDR);
		}
	}
}
