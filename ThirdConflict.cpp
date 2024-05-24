#include "ThirdConflict.hpp"

void ThirdConflict(Character* player1, NpCharacter* enemy)
{
	std::cout << std::endl;
	std::cout << "--- What is Happening? ---" << std::endl;
	std::cout << "The goblin warrior is dead, but still you try to understand what is happening down there, so you hear loud footsteps that sounds like steel shaking" << std::endl;
	std::cout << "it must be the scream the warrior shout earlier, it must had alerted the others, you don't know how much of then are coming, so you decide to hide" << std::endl;
	std::cout << "hidden in the shadows of a tree, you see two goblins running toward the direction of the last conflict" << std::endl;
	std::cout << "one of then is very big with lots of armory, the other carry a cold and creepy presence, they see the carcass of the rebel goblin, and the body of the warrior" << std::endl;
	std::cout << "the creepy one say something in a strange language while takes the carcass of the rebel goblin away to the way they came" << std::endl;
	std::cout << "the armored goblin start to chant a profane music walking around the body of the fallen warrior, until it stabs his dead heart" << std::endl;
	std::cout << "then you see something like a profane soul leaving the dead body, it makes a whisper at the armored ears before fading back to the ground " << std::endl;
	std::cout << "he slowly looks your direction and begin to run laughing, a creepy laugh" << std::endl;
	std::cout << std::endl;

	while (enemy->isAlive() == true && player1->isAlive() == true)
	{
		enemy->basicAttack(player1);
		if (player1->isAlive() == true) {
			player1->showCombatLayout(enemy);
		}
	}
	if (enemy->isAlive() == false)
	{
		std::cout << "The " << enemy->getName() << " falls down" << std::endl;
		player1->increaseExp(enemy);
		delete enemy;
	}
	else if (player1->isAlive() == false)
	{
		std::cout << player1->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete player1;
		exit(0);
	}
}