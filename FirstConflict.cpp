#include "FirstConflict.hpp"

void FirstConflict(Character* player1, NpCharacter* enemy) 
{
	std::cout << std::endl;
	std::cout << "--- So... i gotta eat him ? ---" << std::endl;
	std::cout << "You are walking down a silent forest, anywhere you look there are nothing, the only sound you hear is the noise of your belly wanting something to eat" << std::endl;
	std::cout << "This sound was enought to draw attention to you from a misterious creature that was hidden next to you" << std::endl;
	std::cout << "it suddently jumps out of the bush and you can see him, a starving wounded goblin that will do anything to eat you and recover energy to come back home" << std::endl;
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
		std::cout << "The " << enemy->getName() << " fall down" << std::endl;
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
