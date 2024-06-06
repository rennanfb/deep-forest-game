#include "Conflict2.hpp"

void Conflict2(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- They Found Him -------------------------------" << std::endl;
	std::cout << "After kill your hungry, you lay down to rest, thoughts about how the nature" << std::endl;
	std::cout << "can be violent when there's someone starving" << std::endl;
	std::cout << "you berely close your eyes when you hear a screaming shout coming to you" << std::endl;
	std::cout << "it seems to echo around the forest, it puts you on high alert" << std::endl;
	std::cout << "by your side there is another goblin, he appears to be very angry " << std::endl;
	std::cout << "because what you did, but you cannot understand his langueage" << std::endl;
	std::cout << "he draws his sword and charges into you" << std::endl;
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
		std::cout << "The " << enemies[0]->getName() << " falls down" << std::endl;
		players[0]->increaseExp(enemies[0]);
		delete enemies[0];
	}
	else if (players[0]->isAlive() == false)
	{
		std::cout << players[0]->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete players[0];
		exit(0);
	}
}
