#include "Conflict1.hpp"

void Conflict1(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- So... i gotta eat him ? -------------------------------" << std::endl;
	std::cout << "You are walking down a silent forest, anywhere you look there are nothing" << std::endl;
	std::cout << "the only sound you hear is the noise of your belly wanting something to eat." << std::endl;
	std::cout << "This was enought to draw attention to you from a misterious creature hidden next to you" << std::endl;
	std::cout << "it suddently jumps out of the bush so you can see him" << std::endl;
	std::cout << "a starving wounded goblin that will do anything to eat you and recover energy to come back home" << std::endl;
	std::cout << std::endl;

	while (players[0]->isAlive() && enemies[0]->isAlive())
	{
		for (NpCharacter* enemy : enemies)
		{
			if (enemy->isDebuffed())
			{
				CombatDebuffMechanic(enemy);
			}

			std::cout << "---------------------------------------------------------------------------" << std::endl;

			if (enemy->isAlive() && enemy->isActive())
			{
				enemy->npcSkillSet(players);

			}
		}
		for (NpCharacter* enemy : enemies)
		{
			if (enemy->isAlive())
			{
				if (enemy->isBuffed())
				{
					CombatBuffMechanic(enemy);
				}
			}
		}

		for (Character* player : players)
		{
			if (player->isDebuffed())
			{
				CombatDebuffMechanic(player);
			}

			std::cout << "---------------------------------------------------------------------------" << std::endl;

			if (player->isAlive() && player->isActive())
			{
				player->showCombatLayout(players, enemies);
			}
			else
			{
				std::cout << player->getName() << " is down" << std::endl;
			}

		}

		for (Character* player : players)
		{
			if (player->isAlive())
			{
				if (player->isBuffed())
				{
					CombatBuffMechanic(player);
				}
			}
		}
	}

	if (!players[0]->isAlive())
	{
		std::cout << "You'are dead" << std::endl;
		delete players[0];
		exit(0);
	}

	for (NpCharacter* enemy : enemies)
	{
		if (!enemy->isAlive())
		{
			if (players.size() == 2)
			{
				players[1]->increaseExp(enemy);
			}
			else if (players.size() == 3)
			{
				players[1]->increaseExp(enemy);
				players[2]->increaseExp(enemy);
			}
			else if (players.size() == 4)
			{
				players[1]->increaseExp(enemy);
				players[2]->increaseExp(enemy);
				players[3]->increaseExp(enemy);
			}

			players[0]->defeatEnemy(enemy);
		}
	}
}
