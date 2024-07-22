#include "GoblinWarrior.hpp"

//Constructor

GoblinWarrior::GoblinWarrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GoblinWarrior* GoblinWarrior::createEnemy()
{
		return new GoblinWarrior("Warrior Gobnier", "Gobnier", "Goblin", 10.0f, 7.0f, 12.0f, 3.0f, 8.0f, 10.0f, 45);
	
}

Bag* GoblinWarrior::createNpcBag()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	std::vector<Item*> npcItems;

	if (chance >= 1 && chance <= 50)
	{
		return new Bag(10, npcItems);
	}
	else
	{
		npcItems.push_back(ElixirSmall::createItem());
		return new Bag(10, npcItems);
	}
}

//Skills Sets

void GoblinWarrior::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;
	std::cout << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 70)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 71 && chance < 90)
	{
		this->stockCharge(players[target]);
	}
	else if (chance >= 91 && chance <= 100)
	{
		this->spinningSlash(players[target]);
	}

}