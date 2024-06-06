#include "TorturerZulmin.hpp"

//Constructor

TorturerZulmin::TorturerZulmin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

TorturerZulmin* TorturerZulmin::createEnemy()
{
	return new TorturerZulmin("Torturer Zulmin", "Gobnier", "Goblin", 12.0f, 12.0f, 20.0f, 18.0f, 12.0f, 85);

}

//Skills Sets

void TorturerZulmin::npcSkillSet(std::vector <Character*> players) 
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	int target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 20)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 21 && chance < 85)
	{
		this->throwDagger(players[target]);
	}
	else if (chance >= 86 && chance <= 100)
	{
		this->shadowEmbrace(players[target]);
	}

}