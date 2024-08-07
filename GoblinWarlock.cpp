#include "GoblinWarlock.hpp"

//Constructor

GoblinWarlock::GoblinWarlock(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GoblinWarlock* GoblinWarlock::createEnemy()
{
	return new GoblinWarlock("Warlock Goblin", "Gobnier", "Goblin", 12.0f, 12.0f, 20.0f, 25.0f, 23.0f, 17.0f, 276);

}

Bag* GoblinWarlock::createNpcBag()
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

void GoblinWarlock::npcSkillSet(std::vector <Character*> players)
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
		this->shadowEmbrace(players[target]);
	}
	else if (chance >= 91 && chance <= 100)
	{
		this->bloodBait(players[target]);
	}

}