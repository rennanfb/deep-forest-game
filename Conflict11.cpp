#include "Conflict11.hpp"

void Conflict11(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- There is no peace -------------------------------" << std::endl;
	std::cout << "At this moment you feel lost, Luna was created at the temple, and don't know a lot" << std::endl;
	std::cout << "of the world outside, so you decide to go with Qing to his village, searching for" << std::endl;
	std::cout << "some answers and directions." << std::endl;
	std::cout << "It was a long day of walk before getting near the village, by night, with the sun" << std::endl;
	std::cout << "gone, you can see the orange sky of fire in the direction of the village." << std::endl;
	std::cout << std::endl;
	std::cout << "Qing: My people are being attacked !" << std::endl;
	std::cout << std::endl;
	std::cout << "He says it with despair on his voice then starts to run towards there, you can't" << std::endl;
	std::cout << "let him do it alone and go with him." << std::endl;
	std::cout << "At the entrace of the village, a ending battle can be seem, the greatest hero of" << std::endl;
	std::cout << "Azaya is falling down, after a strange elf crush his body with an unknown magic" << std::endl;
	std::cout << std::endl;
	std::cout << "Qing: what have you done with Zatras!? i'll make you pay with your life..." << std::endl;
	std::cout << std::endl;
	std::cout << "Zatras: run Qing, you can't defeat him, he is... Seiren, from the elder elven" << std::endl;
	std::cout << "forbidden book, you have to... warn... the temple of the sun..." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: the temple of the sun is taken by the demons... if this is really Seiren" << std::endl;
	std::cout << "we need to kill him, he was the betrayer of the old elves centuries ago, he's" << std::endl;
	std::cout << "the most feared dark alchemist that ever existed, his existence is dangerous" << std::endl;
	std::cout << std::endl;
	std::cout << "Seiren: Your name is Luna, i know you, i read your name at the Everbook, yes..." << std::endl;
	std::cout << "want to hear how you will die? or maybe i can show you, i can even bring you back" << std::endl;
	std::cout << "for you to know the truth after this trip..." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: we can't hear him, his word are like poison, let's seize that he is weak" << std::endl;
	std::cout << "after the fight with that Azaya hero" << std::endl;
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
	std::cout << "While the Seiren's body falls the hidden azaya people starts to leave their hideouts" << std::endl;
	std::cout << "there are very few of them, most of the village is dead, it is a sad moment for them." << std::endl;
	std::cout << "Suddenly a suspect cloaked person arrives from the nowhere, catch the body of Seiren" << std::endl;
	std::cout << "Then in a blink of an eye, they disappear, leaving no traces." << std::endl;
	std::cout << std::endl;
	std::cout << "Qing: Thank you so much for your help, if you wasn't here, i dont know... the things" << std::endl;
	std::cout << "could be so much worse now." << std::endl;
	std::cout << "The village survivors are to sad to applaud you but, they all bow to you in gratitude" << std::endl;
	std::cout << std::endl;

}