#include "Conflict1.hpp"

void Conflict1(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- So... i gotta eat him ? -------------------------------" << std::endl;
	std::cout << "You are walking down a silent forest, anywhere you look there are nothing" << std::endl;
	std::cout << "the only sound you hear is the noise of your belly wanting something to eat." << std::endl;
	std::cout << "This was enought to draw attention to you from a misterious creature hidden next to you" << std::endl;
	std::cout << "it suddently jumps out of the bush so you can see him" << std::endl;
	std::cout << "a starving wounded goblin that will do anything to eat you and recover energy to come back home" << std::endl;
	std::cout << std::endl;

	while (players[0]->isAlive() == true && enemies[0]->isAlive() == true)
	{

		enemies[0]->npcSkillSet(players);

		if (players[0]->isAlive() == true)
		{
			players[0]->showCombatLayout(enemies);
		}
	}
	if (enemies[0]->isAlive() == false)
	{
		players[0]->defeatEnemy(enemies[0]);
	}
	else if (players[0]->isAlive() == false)
	{
		std::cout << players[0]->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete players[0];
		exit(0);
	}
}
