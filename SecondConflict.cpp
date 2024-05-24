#include "SecondConflict.hpp"

void SecondConflict(Character* player1, NpCharacter* enemy) 
{
	std::cout << std::endl;
	std::cout << "--- They Found Him ---" << std::endl;
	std::cout << "After kill your hungry, you lay down to rest, thoughts about how the nature can be violent when there's someone starving" << std::endl;
	std::cout << "you berely close your eyes when you hear a screaming shout coming to you" << std::endl;
	std::cout << "it seems to echo around the forest, it puts you on high alert, by your side there is another goblin" << std::endl;
	std::cout << "he appears to be very angry because what you did with the other one, but you cannot understand his langueage" << std::endl;
	std::cout << "he draws his sword and charges into you" << std::endl;
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
