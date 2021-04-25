#ifndef CREATURE_H
#define CREATURE_H
#include <utility>

class Creature
{
private:

	std::pair<int,int> calcCurrentTile(); // calculate current tile
	bool atCenter; // synchronizing boolean. Invoke onTileCenter only once!
	bool isCenterTile();

public:
	
	virtual ~Creature() {};
	Creature(int x, int y, float z);

	float x, y, z;  
	int tileX;
	int tileY;

	int lives;
	double angle;
	double speed;
	bool moving;

	void Reassign(int,int);
	std::pair<int, int> Move();
	void Pad();
	void PadToCenter(); // makes creature put in the center of the current tile.

	virtual void onTileChange() {}; // on step for a new tile
	virtual void onTileCenter() {}; // when in tile center

};

#endif