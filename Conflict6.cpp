#include "Conflict6.hpp"

void Conflict6(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- The Twin Mercenaries -------------------------------" << std::endl;
	std::cout << "You open your eyes, and you can see them, you've been kidnaped by two rogue gnomes" << std::endl;
	std::cout << "they notice that you're awake." << std::endl;
	std::cout << std::endl;
	std::cout << "Both says: we are Rath and Beth, and by now you are our property, at least until we" << std::endl;
	std::cout << "deliver you to them, it is nothing personal big " << players[0]->getRace() << " just business" << std::endl;
	std::cout << "they are paying so much gold for you, and we want so much gold, you know?!" << std::endl;
	std::cout  << std::endl;
	std::cout << "You have no much to do by now, imprisoned without your waepons, then you are hit by a" << std::endl;
	std::cout << "paper ball that says: be ready now." << std::endl;
	std::cout << std::endl;
	std::cout << "Rath: i dont really know why you're worth so much gold, you seem a bit ordinary to me..." << std::endl;
	std::cout << std::endl;
	std::cout << "Then a sudden fog takes the environment, nobody can see nothing for this moment, you feel" << std::endl;
	std::cout << "the chains and cage breaking, your waepon suddenly is at your hand, you can't understand" << std::endl;
	std::cout << "but there's no time to think, the fog disappears..." << std::endl;
	std::cout << std::endl;
	std::cout << "Both says: THE GOLD WERE FREED, GET HIM!!" << std::endl;
	std::cout << std::endl;


	while (players[0]->isAlive() && (enemies[0]->isAlive() || enemies[1]->isAlive()))
	{
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

		for (NpCharacter* enemy : enemies)
		{
			std::cout << "---------------------------------------------------------------------------" << std::endl;
			if (enemy->isAlive())
			{
				enemy->npcSkillSet(players);
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

	std::cout << std::endl;
	std::cout << "You win this unfair battle, and hear applauses coming from behind you" << std::endl;
	std::cout << "you look back and theres a man in a hood, he says:" << std::endl;
	std::cout << std::endl;
	std::cout << "The unknown has met you, now you are followed by unexpected dangers" << std::endl;
	std::cout << "but you're lucky that we're following you too, and we need your help" << std::endl;
	std::cout << "you can call me Tonius, i'm one of the three truth prophets" << std::endl;
	std::cout << std::endl;


}