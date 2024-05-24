#include "FourthConflict.hpp"

void FourthConflict(Character* player1, NpCharacter* enemy, NpCharacter* enemy2) 
{
	std::cout << std::endl;
	std::cout << "--- Is he alive? ---" << std::endl;
	std::cout << "The dark paladin is dead, his body goes down the river he fell, this place is dangerous, something is happening nearby with these goblins" << std::endl;
	std::cout << "you notice that he seemed to eat a lot, it could be a good ideia to go look for food from the place they came, it could help to hang the trip" << std::endl;
	std::cout << "the problem is, that other creepy cold goblin must be there, but you had already killer three of them, if anything goes wrong, you'll handle it" << std::endl;
	std::cout << "while approaching the campsite, you notice that is a very small camp with only one tent, you can hear strange noises coming from inside" << std::endl;
	std::cout << "next to the tent entrace, you see the creepy goblin torturing the carcass of the first goblin you killed, and the worst, he seems to be alive again" << std::endl;
	std::cout << "what kind of evil sorcery is this... necromancy? it must be why the first goblin was hidding alone, he was been chased for the worst kind of questioning" << std::endl;
	std::cout << "how could someone use dark sorcery to torture a dead soul for answers? that first goblin should know something very important" << std::endl;
	std::cout << "you're astonished with what you just saw, and with no time to recompose yourself, you hear..." << std::endl;
	std::cout << std::endl;
	std::cout << "Torturer Zulmin: will you stay with this ugly face in this entrace for how long?" << std::endl;
	std::cout << std::endl;
	std::cout << "this creepy goblin can talk your language, but now is not a good moment to talk, you should just get some food and go but, this all was so unsettling" << std::endl;
	std::cout << std::endl;
	std::cout << "Torturer Zulmin: you know... i hate these appostates, but theres a thing i hate more... your kind... i will alow him to feast revenge upon you" << std::endl;
	std::cout << std::endl;

	while (player1->isAlive() == true && (enemy2->isAlive() == true || enemy->isAlive() == true))
	{
		if (enemy2->isAlive() == true)
		{
			enemy2->basicAttack(player1);	
		}

		bool target = false;

		if (enemy->isAlive() == true && enemy2->isAlive() == true)
		{
			while (!target)
			{
				std::cout << "Choose your target: Enter (1) for Zombie Goblin | Enter (2) for Torturer Zulmin" << std::endl;

				int answer;
				std::cin >> answer;

				if (answer == 1)
				{
					player1->showCombatLayout(enemy2);
					target = true;
				}
				else if (answer == 2)
				{
					player1->showCombatLayout(enemy);
					target = true;
				}
				else
				{
					std::cout << "Please enter (1 or 2)." << std::endl;
				}
			}
		}
		else
		{ 
			if (enemy->isAlive() == true) 
			{
				player1->showCombatLayout(enemy);
			}
			else if (enemy2->isAlive() == true) 
			{
				player1->showCombatLayout(enemy2);
			}

		}

		if (enemy->isAlive() == true)
		{
			enemy->basicAttack(player1);
		}

	}
	if (enemy->isAlive() == false && enemy2->isAlive() == false)
	{
		std::cout << "The " << enemy->getName() << " and " << enemy2->getName() << " are down" << std::endl;
		player1->increaseExp(enemy);
		player1->increaseExp(enemy2);
		delete enemy;
		delete enemy2;

	}
	else if (player1->isAlive() == false)
	{
		std::cout << player1->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete player1;
		exit(0);
	}
}