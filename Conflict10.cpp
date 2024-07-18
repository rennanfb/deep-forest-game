#include "Conflict10.hpp"

void Conflict10(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- Old Legends -------------------------------" << std::endl;
	std::cout << "You can see how Luna's skills are useful, and that it's a gift to have her" << std::endl;
	std::cout << "by your side, the best gift to anyone who fears death." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: You really fight like a hero, but i think we are trapped in this deep" << std::endl;
	std::cout << "forest, this is a forbidden place you know? there's legends about this place" << std::endl;
	std::cout << "some say that the forest hides a window to another world, that's why the temple" << std::endl;
	std::cout << "is around here, it was like a lighthouse against the unknown" << std::endl;
	std::cout << std::endl;
	std::cout << "When she says that, you feel a shiver, that made you realize that you don't" << std::endl;
	std::cout << "really remember what you were doing before enter this forest, at this moment" << std::endl;
	std::cout << "you feel that there's someone behind you, and it makes you wildly scream" << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: What happened?! " << std::endl;
	std::cout << std::endl;
	std::cout << "Then you hear a roar very much louder than your last scream, something had" << std::endl;
	std::cout << "spotted your location, and you can feel his loud steps approaching..." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: I think we don't have time to hide, what should we do?" << std::endl;
	std::cout << std::endl;
	std::cout << "As it approaches you notice something like a colossal lion, but there is " << std::endl;
	std::cout << "another goat head, and theres a giant snake around it, it arrives at you " << std::endl;
	std::cout << "knocking down the trees on the way." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: this is unbeliavable, i thought the chimeras were another legend..." << std::endl;

	while (players[0]->isAlive() && (enemies[0]->isAlive()))
	{
		for (Character* player : players)
		{
			std::cout << "---------------------------------------------------------------------------" << std::endl;
			if (player->isAlive())
			{
				player->showCombatLayout(players, enemies);
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
			players[1]->increaseExp(enemy);

			players[0]->defeatEnemy(enemy);
		}
	}

	std::cout << std::endl;
	std::cout << "When you get near the chimera's body, you saw an arrow coming from the woods" << std::endl;
	std::cout << "it made you get back..." << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: Maybe some of the natives?" << std::endl;
	std::cout << std::endl;
	std::cout << "Strange: don't touch the chimera's body, it's mine, i've been tracking this" << std::endl;
	std::cout << "creature for days" << std::endl;
	std::cout << std::endl;
	std::cout << "Luna: We don't want this corpse, i can have it, why were you chasing this, or" << std::endl;
	std::cout << "better, why is this doing around here, chimeras wasn't supposed to be legens?" << std::endl;
	std::cout << std::endl;
	std::cout << "Qing: My name is Qing, some days ago something strange happened in this woods," << std::endl;
	std::cout << "ancient creatures are coming, my people believe theres something to do with " << std::endl;
	std::cout << "the ancient window that lay somewhere in this forest" << std::endl;
}