#include "Conflict5.hpp"

void Conflict5(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- Am i alive ? -------------------------------" << std::endl;
	std::cout << "You feel sinking into a deep dark ocean, with countless silhouettes swimming" << std::endl;
	std::cout << "in a way that seems to be a desperate dance with screamings of emotional pain" << std::endl;
	std::cout << "between these horrors you hear an awful laughter followed by seductive words" << std::endl;
	std::cout << std::endl;
	std::cout << "Unknown: Come to me child, i can give you exactly it all that you want..." << std::endl;
	std::cout << std::endl;
	std::cout << "After these words you feel yourself splitting in half, becoming a light silhouette" << std::endl;
	std::cout << "as your phisycal silhouette run away from your light following the unknown's voice" << std::endl;
	std::cout << "the more it goes away, more your light fades, so you decide to try to prevent yourself" << std::endl;
	std::cout << "to follow the dark chant, as close you get from yourself, more the other part try to" << std::endl;
	std::cout << "run away from you, until it screams and attack you" << std::endl;
	std::cout << std::endl;

	while (enemies[0]->isAlive() && players[0]->isAlive())
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

	std::cout << "After the last strike, your ego starts to cry and it slowly unites with you again" << std::endl;
	std::cout << "you feel a great eye opening inside your mind for a moment, before you wake up" << std::endl;
	std::cout << "as you get awake, you hear chains shaking, you're imprisoned." << std::endl;
}
