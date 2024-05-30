#include "Conflict2.hpp"

void Conflict2(Character* player1, std::vector<NpCharacter*> enemies)
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

	while (player1->isAlive() == true && enemies[0]->isAlive() == true)
	{
		enemies[0]->npcSkillSet(enemies[0], player1);

		player1->showCombatLayout(enemies);
	}
	if (enemies[0]->isAlive() == false)
	{
		std::cout << "The " << enemies[0]->getName() << " falls down" << std::endl;
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
