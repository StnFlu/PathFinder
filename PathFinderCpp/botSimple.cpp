#include "bots.h"

void cBotSimple::ChooseNextGridPosition()
{
	int posX = PositionX();
	int posY = PositionY();

	int targetPosX = gTarget.PositionX();
	int targetPosY = gTarget.PositionY();

	int xDir = 0;
	int yDir = 0;

	bool xDire = true;
	bool yDire = true;

	if (PositionX() > gTarget.PositionX() || PositionX() < gTarget.PositionX())
	{
		if (PositionX() < gTarget.PositionX())
			xDir = 1;
		else
			xDir = -1;
		xDire = false;
	}
	else if (PositionY() > gTarget.PositionY() || PositionY() < gTarget.PositionY())
	{
		if (PositionY() < gTarget.PositionY())
			yDir = 1;
		else
			yDir = -1;
		yDire = false;
	}


	if (gLevel.isValid(PositionX() + xDir, PositionY()))
	{
		while (!xDire)
		{
			xDire = SetNext(PositionX() + xDir, (PositionY()), gLevel);
		}
	}
	else
	{
		if (gLevel.isValid(PositionX(), PositionY() + yDir))
		{
			if (PositionY() < gTarget.PositionY())
				yDir = 1;
			else if (PositionY() > gTarget.PositionY())
				yDir = -1;
		}
		
			yDir = 0;
			if (!((PositionX() - gTarget.PositionX()) == 0))
			{
				
				yDir = 1;
				yDire = false;
			}
		
			yDire = false;
	}
	while (!yDire && gLevel.isValid(PositionX(), PositionY() + yDir))
	{
		yDire = SetNext(PositionX() , (PositionY() + yDir), gLevel);
	}

}
