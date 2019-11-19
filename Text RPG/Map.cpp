#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	mPlayerPosition.x = 0;
	mPlayerPosition.y = 0;
}

Point Map::getPlayerPosition()
{
	return mPlayerPosition;
}

void Map::movePlayer()
{
	while (true)
	{
		int selection = 1;
		std::cout << "1) North, 2) East, 3) South, 4) West: ";
		std::cin >> selection;
		std::cout << std::endl;

		switch (selection)
		{
		case 1:
			mPlayerPosition.y++;
			return;
		case 2:
			mPlayerPosition.x++;
			return;
		case 3:
			mPlayerPosition.y--;
			return;
		case 4:
			mPlayerPosition.x--;
			return;
		default:
			std::cout << "Invalid Input!" << std::endl;
			break;
		}
	}
}

Monster * Map::checkRandomEncounter()
{
	int roll = Random(0,20);
	Monster* monster = NULL;

	if(roll <= 5) return NULL;

	if (roll == 20)
		monster = new Monster("Orc Lord", 25, 15, 2000, Random(800, 1200) , 5, "Two Handed Sword", 5, 20);
	else if (roll >= 16)
		monster = new Monster("Ogre", 20, 12, 500, Random(500, 700), 2, "Club", 3, 8);
	else if (roll >= 11)
		monster = new Monster("Goblin", 6, 6, 100, Random(300, 500), 0, "Dagger", 1, 5);
	else
		monster = new Monster("Orc", 10, 8, 200, Random(100, 300), 1,	"Short Sword", 2, 7);

	std::cout << "You encountered an " << monster->getName() << " !" << std::endl;
	std::cout << "Prepare for battle!" << std::endl;
	std::cout << std::endl; 

	return monster;
}

void Map::printPlayerPosition()
{
	std::cout << "Player's position = (" << mPlayerPosition.x << ", " << mPlayerPosition.y << ")" << std::endl << std::endl;
}
