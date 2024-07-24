#include "Conflict2.hpp"

void Conflict2(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- They Found Him -------------------------------" << std::endl;
	std::cout << "After kill your hungry, you lay down to rest, thoughts about how the nature" << std::endl;
	std::cout << "can be violent when there's someone starving" << std::endl;
	std::cout << "you berely close your eyes when you hear a screaming shout coming to you" << std::endl;
	std::cout << "it seems to echo around the forest, it puts you on high alert" << std::endl;
	std::cout << "by your side there is another goblin, he appears to be very angry " << std::endl;
	std::cout << "because what you did, but you cannot understand his langueage" << std::endl;
	std::cout << "he draws his sword and charges into you" << std::endl;
	std::cout << std::endl;

	while (players[0]->isAlive() && enemies[0]->isAlive())
	{
		for (NpCharacter* enemy : enemies)
		{
			std::cout << "---------------------------------------------------------------------------" << std::endl;
			if (enemy->isAlive())
			{
				enemy->npcSkillSet(players);
			}
		}

		for (Character* player : players)
		{
			std::cout << "---------------------------------------------------------------------------" << std::endl;
			if (player->isAlive())
			{
				player->showCombatLayout(players, enemies);
			}
			else
			{
				std::cout << player->getName() << " is down" << std::endl;
			}
		}
	}

	if (!players[0]->isAlive())
	{
		std::cout << players[0]->getName() << " fall down" << std::endl;
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
