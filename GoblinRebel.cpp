#include "GoblinRebel.hpp"

//Constructor

GoblinRebel::GoblinRebel(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GoblinRebel* GoblinRebel::createEnemy()
{
	return new GoblinRebel("Rebel Goblin", "Street", "Goblin", 8.0f, 12.0f, 8.0f, 5.0f, 12.0f, 38);
}

Bag* GoblinRebel::createNpcBag() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	std::vector<Item*> npcItems;

	if (chance >= 1 && chance <= 60) 
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

void GoblinRebel::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 50)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 51 && chance < 80)
	{
		this->throwDagger(players[target]);
	}
	else if (chance >= 81 && chance <= 100)
	{
		this->stockCharge(players[target]);
	}

}