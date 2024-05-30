#include "Conflict1.hpp"

void Conflict1(Character* player1, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- So... i gotta eat him ? -------------------------------" << std::endl;
	std::cout << "You are walking down a silent forest, anywhere you look there are nothing" << std::endl;
	std::cout << "the only sound you hear is the noise of your belly wanting something to eat." << std::endl;
	std::cout << "This was enought to draw attention to you from a misterious creature hidden next to you" << std::endl;
	std::cout << "it suddently jumps out of the bush so you can see him" << std::endl;
	std::cout << "a starving wounded goblin that will do anything to eat you and recover energy to come back home" << std::endl;
	std::cout << std::endl;

	while (player1->isAlive() == true && enemies[0]->isAlive() == true)
	{

		enemies[0]->npcSkillSet(enemies[0], player1);

		if (player1->isAlive() == true) {
			player1->showCombatLayout(enemies);
		}
	}
	if (enemies[0]->isAlive() == false)
	{
		std::cout << "The " << enemies[0]->getName() << " fall down" << std::endl;
		player1->increaseExp(enemies[0]);
		delete enemies[0];
	}
	else if (player1->isAlive() == false) 
	{
		std::cout << player1->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete player1;
		exit(0);
	}
}
