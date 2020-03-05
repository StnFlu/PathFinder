#include "bots.h"
#include <stdio.h>

void cDijkstra::Build(cBotBase& bot)
{
	bool running = true;
	for (int w = 0; GRIDWIDTH > w; w++)
	{
		for (int h = 0; GRIDHEIGHT > h; h++)
		{
			closed[w][h] = false;
			cost[w][h] = 1000000.0f;
			linkX[w][h] = -1;
			linkY[w][h] = -1;
			inPath[w][h] = false;
			running = false;
			
		}
	}

	cost[bot.PositionX()][bot.PositionY()] = 0;

	while (!running)
	{
		

		int lowestW = 0;
		int lowestH = 0;
		for (int w = 0; GRIDWIDTH > w; w++)
		{
			for (int h = 0; GRIDHEIGHT > h; h++)
			{
				if (cost[w][h] <= cost[lowestH][lowestW] && !closed[w][h])
				{
					lowestW = w;
					lowestH = h;
				}
			}
		}

		closed[lowestW][lowestH] = true;
		
		if (lowestW == gTarget.PositionX() && lowestH == gTarget.PositionY())
		{
			running = true;
		}

		if (gLevel.isValid(lowestW + 1, lowestH) && !closed[lowestW + 1][lowestH])
		{
			cost[lowestW + 1][lowestH] = cost[lowestW][lowestH] + 1; // right
			linkX[lowestW + 1][lowestH] = lowestW;
			linkY[lowestW + 1][lowestH] = lowestH;
		}
		if (gLevel.isValid(lowestW - 1, lowestH) && !closed[lowestW - 1][lowestH])
		{
			cost[lowestW - 1][lowestH] = cost[lowestW][lowestH] + 1; // left
			linkX[lowestW - 1][lowestH] = lowestW;
			linkY[lowestW - 1][lowestH] = lowestH;
		}
		if (gLevel.isValid(lowestW, lowestH+1) && !closed[lowestW][lowestH +1])
		{
			cost[lowestW][lowestH + 1] = cost[lowestW][lowestH] + 1; // Up
			linkX[lowestW][lowestH + 1] = lowestW;
			linkY[lowestW][lowestH + 1] = lowestH;
		}
		if (gLevel.isValid(lowestW, lowestH-1) && !closed[lowestW][lowestH-1])
		{
			cost[lowestW][lowestH - 1] = cost[lowestW][lowestH] + 1; // Down
			linkX[lowestW - 1][lowestH] = lowestW;
			linkY[lowestW - 1][lowestH] = lowestH;
		}
		if (gLevel.isValid(lowestW - 1, lowestH-1) && !closed[lowestW - 1][lowestH -1])
		{
			cost[lowestW - 1][lowestH - 1] = cost[lowestW][lowestH] + 1.4f; // DownLeft
			linkX[lowestW - 1][lowestH - 1] = lowestW;
			linkY[lowestW - 1][lowestH - 1] = lowestH;
		}
		if (gLevel.isValid(lowestW + 1, lowestH - 1) && !closed[lowestW + 1][lowestH - 1])
		{
			cost[lowestW + 1][lowestH - 1] = cost[lowestW][lowestH] + 1.4f; // DownRight
			linkX[lowestW + 1][lowestH - 1] = lowestW;
			linkY[lowestW + 1][lowestH - 1] = lowestH;
		}
		if (gLevel.isValid(lowestW - 1, lowestH +1) && !closed[lowestW - 1][lowestH +1])
		{
			cost[lowestW - 1][lowestH + 1] = cost[lowestW][lowestH] + 1.4f; // UpLeft
			linkX[lowestW - 1][lowestH + 1] = lowestW;
			linkY[lowestW - 1][lowestH + 1] = lowestH;
		}
		if (gLevel.isValid(lowestW + 1, lowestH + 1) && !closed[lowestW + 1][lowestH + 1])
		{
			cost[lowestW + 1][lowestH + 1] = cost[lowestW][lowestH] + 1.4f; // UpRight
			linkX[lowestW + 1][lowestH + 1] = lowestW;
			linkY[lowestW + 1][lowestH + 1] = lowestH;
		}
		
	}
	
	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];

		if ((nextClosedX == bot.PositionX()) && (nextClosedY ==
			bot.PositionY()))
		{	
			printf("done");
			done = true;
		}
	}

	
	completed = true;
}

cDijkstra gDijkstra;