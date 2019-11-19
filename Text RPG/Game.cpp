#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
	srand( time(0) );

	Map		game_map;
	Player	main_player;

	main_player.createClass();

	bool game_over = false;

	while (!game_over)
	{
		game_map.printPlayerPosition();

		int selection = 1;
		std::cout << "1) Move, 2) Rest, 3) View Stats, 4) Quit: ";
		std::cin >> selection;

		Monster* monster = NULL;

		switch (selection)
		{
		case 1:
			game_map.movePlayer();

			monster = game_map.checkRandomEncounter();

			if (monster)
			{
				while (true)
				{
					main_player.displayHPandMP();
					std::cout << std::endl;
					monster->displayHitPoints();
					std::cout << std::endl;

					bool run = main_player.attack(*monster);

					if(run) break;

					if (monster->isDead())
					{
						main_player.victory(monster->getXPReward(), monster->getGoldReward());
						main_player.levelUp();
						break;
					}

					monster->attack(main_player);

					if (main_player.isDead())
					{
						main_player.gameover();
						game_over = true;
						break;
					}
				}

				delete monster;
				monster = NULL;
			}

			break;

		case 2:
			main_player.rest();
			break;
		case 3:
			main_player.viewStats();
			break;
		case 4:
			game_over = true;
			break;
		}
	}
}