#include "GoblinPaladin.hpp"

//Constructor

GoblinPaladin::GoblinPaladin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GoblinPaladin* GoblinPaladin::createEnemy()
{
	return new GoblinPaladin("Paladin Gobnier", "Gobnier", "Goblin", 12.0f, 4.0f, 15.0f, 7.0f, 8.0f, 8.0f, 60);

}

Bag* GoblinPaladin::createNpcBag()
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
	else if (chance >= 61 && chance <= 90)
	{
		npcItems.push_back(ElixirSmall::createItem());
		return new Bag(10, npcItems);
	}
	else
	{
		npcItems.push_back(ElixirMedium::createItem());
		return new Bag(10, npcItems);
	}

}

//Skills Sets

void GoblinPaladin::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;
	std::cout << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 75)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 76 && chance < 100)
	{
		this->shieldBash(players[target]);
	}

}