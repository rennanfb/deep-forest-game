#include "Conflict8.hpp"

void Conflict8(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- The Priestess of the sun -------------------------------" << std::endl;
	std::cout << "You were hours thinking about the last events when you hear a woman's voice screaming" << std::endl;
	std::cout << "she is running towards your direction, so you can see, she is beeing followed by three" << std::endl;
	std::cout << "figures, a demon accompanied by two goblins." << std::endl;
	std::cout << std::endl;
	std::cout << "Demon: End of the line fake priestess, the messiah has surrounded you..." << std::endl;
	std::cout << std::endl;
	std::cout << "The demon seems to be talking about you, just like the prophet said, he talks like he knows" << std::endl;
	std::cout << "you, but you never saw that thing before." << std::endl;
	std::cout << std::endl;
	std::cout << "Demon: Kill her master, stop her silly talk about the light, it makes me want to vomit" << std::endl;
	std::cout << "you didn't know me yet, but i know you, my name is Aztras, and i'm ready to answer your call" << std::endl;
	std::cout << std::endl;
	std::cout << "Priestess: Help me stranger, don't let his manipulation get to you, i can see the light in you" << std::endl;
	std::cout << "it is the brighter i ever saw in this lifetime, i know you can be trusted." << std::endl;
	std::cout << std::endl;
	std::cout << "You are confused, but you can't let these creatures hurt this woman, so you grab your waepon" << std::endl;
	std::cout << "and gave a imposing look over the demon." << std::endl;
	std::cout << std::endl;
	std::cout << "Aztras: Why are you looking at me this way? am i not worthy ?" << std::endl;
	std::cout << std::endl;
	std::cout << "Priestess: He can see through your lies demon, he is not your messiah, his light is" << std::endl;
	std::cout << "strong enough to make your shadow leave this world" << std::endl;
	std::cout << std::endl;
	std::cout << "Aztras: Well, let me take the proof, if he is the messiah, i could never defeat him" << std::endl;
	std::cout << "so theres nothing to lose if i try to end him, if i do, he is not the messiah" << std::endl;
	std::cout << std::endl;


	while (players[0]->isAlive() && (enemies[0]->isAlive() || enemies[1]->isAlive() || enemies[2]->isAlive()))
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

	std::cout << std::endl;
	std::cout << "Aztras: We'll met again messiah, you can't run from fate..." << std::endl;
	std::cout << std::endl;
	std::cout << "Priestess: You... thank you, my name is Luna, i serve the order" << std::endl;
	std::cout << "of Sundeva, our mission is to tell the tale of the cosmic energy" << std::endl;
	std::cout << "of the light in union with the ether. " << std::endl;
	std::cout << std::endl;

}