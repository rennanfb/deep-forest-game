#include "Conflict9.hpp"

void Conflict9(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- Causality Meeting -------------------------------" << std::endl;
	std::cout << "After the battle the night falls, but even in the dark you could notice the sad" << std::endl;
	std::cout << "eyes of Luna, you can feel the sadness in the air, something is wrong..." << std::endl;
	std::cout << std::endl;
	std::cout << "Tonius: You lost the plot young " << players[0]->getName() << ", the unknow has seem you" << std::endl;
	std::cout << "i told you your journey would be hard, but its getting worse so much faster than " << std::endl;
	std::cout << "i could foresee... the demons... they came here searching for you, and they found" << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: Us... the order of the sun... Sundeva... now is no more, when i found you" << std::endl;
	std::cout << "i was running from then, they destroyed our temple, killed everyone, at this point" << std::endl;
	std::cout << "i don't know if there are anyone alive..." << std::endl;
	std::cout << std::endl;
	std::cout << "Tonius: Luna, i know how hard is for mortals to accept the idea of death, but you" << std::endl;
	std::cout << "have to understand, the causality, it is a divine concept, the reality is just the" << std::endl;
	std::cout << "way it should be, as priestess of Sundeva i know you understands" << std::endl;
	std::cout <<  std::endl;
	std::cout << "Luna: Wait, i think i know you, you are one of the Truth Aspects, i didn't even knew" << std::endl;
	std::cout << "you were literally physical beings, i'm honored, and you're right, maybe, i " << std::endl;
	std::cout << "should be here, that's why i'm talking to you..." << std::endl;
	std::cout << std::endl;
	std::cout << "Tonius: but there's no time to talk young Luna, i'm just here to advice you two" << std::endl;
	std::cout << "that the truth need you two to be together, causality built this, you have an" << std::endl;
	std::cout << "important role with his hero's journey, this is what the light reaveals..." << std::endl;
	std::cout << std::endl;
	std::cout << "Tonius: And for you young hero... i advice you to don't desappear in the dark and to" << std::endl;
	std::cout << "don't get blinded by the light" << std::endl;
	std::cout << std::endl;
	std::cout << "And then, he disappeared like he was not really there, you're with Luna in the " << std::endl;
	std::cout << "deep dark forest, and you think it's your fault that her temple was destroyed" << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: So... you are a hero of the truth?" << std::endl;
	std::cout << std::endl;
	std::cout << "Before you can answer, you feel a shiver down the spine, when you notice you two" << std::endl;
	std::cout << "are surrounded by five hungry Saberwolves" << std::endl;

	while (players[0]->isAlive() && (enemies[0]->isAlive() || enemies[1]->isAlive() || enemies[2]->isAlive() || enemies[3]->isAlive() || enemies[4]->isAlive()))
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
	std::cout << "Luna: Thank you " << players[0]->getName() << ", if wasn't for you, i don't know..." << std::endl;
	std::cout << "i grew up at the temple, i've never killed anything before, sorry, i'm nervous" << std::endl;
	std::cout << "but i feel like i'm stronger after this fight,i would feel better if i could only" << std::endl;
	std::cout << "help you with healing, but, i had to hurt then too, they were only hungry animals... " << std::endl;
	std::cout << std::endl;
	std::cout << "You are more used to this survival feeling, and she is happy that you're with her" << std::endl;
	std::cout << "right now, it seems like she doesn't have a place to go back." << std::endl;

}