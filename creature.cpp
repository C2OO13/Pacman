#define _USE_MATH_DEFINES
#include <utility>
#include <cmath>
#include "creature.h"
#include <iostream>

// Difference between current position and the tile center.
static const double CENTER_DIM = 0.05;

Creature::Creature(int x_b, int y_b, float z_b)
{
	x = x_b;
	y = y_b;
	z = z_b;
	tileX = x_b;
	tileY = y_b;

	atCenter = true;
}

std::pair<int,int> Creature::calcCurrentTile()
{
	if ((angle == 0) && ((x - (int)x) > 0.5))
		tileX = (int)ceil(x);
	if ((angle == 180) && ((x - (int)x) < 0.5))
		tileX = (int)floor(x);
	if ((angle == 90) && ((y - (int)y) > 0.5))
		tileY = (int)ceil(y);
	if ((angle == 270) && ((y - (int)y) < 0.5))
		tileY = (int)floor(y);
	std::pair<int, int> p = { tileX,tileY };
	return p;
}

bool Creature::isCenterTile()
{
	return (
		((angle == 0)   && (x - (int)x > 1 - CENTER_DIM)) ||
	    ((angle == 180) && (x - (int)x < CENTER_DIM))     ||
	    ((angle == 90)  && (y - (int)y > 1 - CENTER_DIM)) ||
	    ((angle == 270) && (y - (int)y < CENTER_DIM)))    ? true : false;
}


void Creature::Reassign(int X, int Y)
{
	x = X;
	y = Y;
}

// Basic movement algorithm.
std::pair<int, int> Creature::Move()
{
	if (moving) 
	{
		x += speed*cos(M_PI/180*angle);
		y += speed*sin(M_PI/180*angle);

		if (!atCenter && isCenterTile())
		{
			atCenter = true;
			onTileCenter();
		}
	}

	int oldTileX = tileX;
	int oldTileY = tileY;

	std::pair<int,int> p = calcCurrentTile();
	//std::cout<<p.first<<" "<<p.second<<"\n";
	if (tileX != oldTileX || tileY != oldTileY)
	{
		atCenter = false;  
		onTileChange(); 
	}
	return p;
}

void Creature::Pad()
{
	x = (int)x;
	y = (int)y;
}

void Creature::PadToCenter()
{
	x = tileX;
	y = tileY;
}