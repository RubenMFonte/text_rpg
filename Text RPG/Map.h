#pragma once

#include "Weapon.h"
#include "Monster.h"
#include <string>

struct Point
{
	int x;
	int y;
};

class Map
{
public:
	Map();

	Point getPlayerPosition();
	void movePlayer();
	Monster* checkRandomEncounter();
	void printPlayerPosition();

private:
	Point mPlayerPosition;
};
