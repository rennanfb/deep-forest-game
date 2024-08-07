#include "Conflict7.hpp"

void Conflict7(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- The Truth? -------------------------------" << std::endl;
	std::cout << "Tonius: i'm the one that saved you with that fog, but i should not had done that" << std::endl;
	std::cout << "the Truth Prophets are not allowed to intervene with the mortal souls, but" << std::endl;
	std::cout << "given the circunstances i guess it is okay by now, after all, you had just" << std::endl;
	std::cout << "passed through a spiritual trip with the unknown and slept for 2 days..." << std::endl;
	std::cout << std::endl;
	std::cout << "The prophet talk to you about strange things like you know what is he saying" << std::endl;
	std::cout << "but it not make all sense to you yet, you don't really know what happened that day" << std::endl;
	std::cout << std::endl;
	std::cout << "Tonius: I know it all seems so strange for you, but right now, you only need to" << std::endl;
	std::cout << "know that, what you saw in that dream, was the truth, but not all the truth..." << std::endl;
	std::cout << "some people will come for you, wanting you as a messiah, but i beg you to follow" << std::endl;
	std::cout << "your light and not your ego, you're about to make great thing in this world" << std::endl;
	std::cout << std::endl;
	std::cout << "Then he fades, like he was never really there, you're astonished with his speech" << std::endl;
	std::cout << "but you can't think about that with 2 days of starving scratching your belly." << std::endl;
	std::cout << std::endl;
	std::cout << "Echoing through the forest you can hear a loud beast scream, you can't think twice" << std::endl;
	std::cout << "and just moves that way, where you can see a Colossal Boar wandering around" << std::endl;
	std::cout << "that's a lot of meat." << std::endl;
	std::cout << std::endl;

	while (players[0]->isAlive() && enemies[0]->isAlive())
	{
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

	std::cout << "You kill your hungry, while thinks about what the prophet told you... messiah?" << std::endl;
	std::cout << "for a moment you try to understant what was that leaving your body after" << std::endl;
	std::cout << "kill the Torturer Goblin and the zombie goblin, suddenly passes through your mind" << std::endl;
	std::cout << "that maybe was that dark magic with the body of the zombie goblin, there was parts" << std::endl;
	std::cout << "of him in you, you had just ate him to kill your hungry at that moment." << std::endl;
}