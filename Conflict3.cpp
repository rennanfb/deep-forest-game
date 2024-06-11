#include "Conflict3.hpp"

void Conflict3(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- What is Happening? -------------------------------" << std::endl;
	std::cout << "The goblin warrior is dead, but still you try to understand what is " << std::endl;
	std::cout << "happening down there. So you hear loud footsteps that sounds like steel shaking" << std::endl;
	std::cout << "it must be the scream the warrior shout earlier, it must had alerted the others" << std::endl;
	std::cout << "you don't know how much of then are coming, so you decide to hide in the bushes" << std::endl;
	std::cout << "you see two goblins running toward the direction of the last conflict" << std::endl;
	std::cout << "one of then is very big with lots of armory, the other carry a cold and " << std::endl;
	std::cout << "creepy presence, they see the bodies of the dead goblins, the creepy one says" << std::endl;
	std::cout << "something in a strange language while takes the carcass of the rebel goblin away" << std::endl;
	std::cout << "the armored goblin start to chant a profane music walking around the body" << std::endl;
	std::cout << "of the fallen warrior, until it stabs his dead heart, then you see something" << std::endl;
	std::cout << "like a profane soul leaving the dead body, it makes a whisper at the armored" << std::endl;
	std::cout << "goblin's ears before fading back to the ground, then he slowly look at you" << std::endl;
	std::cout << "and begin to run laughing, a creepy laugh" << std::endl;
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