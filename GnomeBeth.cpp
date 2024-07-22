#include "GnomeBeth.hpp"

//Constructor

GnomeBeth::GnomeBeth(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GnomeBeth* GnomeBeth::createEnemy()
{
	return new GnomeBeth("Beth", "Street", "Gnome", 17.0f, 10.0f, 15.0f, 5.0f, 16.0f, 20.0f, 90);

}

Bag* GnomeBeth::createNpcBag()
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
		npcItems.push_back(ElixirMedium::createItem());
		return new Bag(10, npcItems);
	}
	else
	{
		npcItems.push_back(ElixirMedium::createItem());
		npcItems.push_back(PotionSmall::createItem());
		return new Bag(10, npcItems);
	}

}

//Skills Sets

void GnomeBeth::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;
	std::cout << std::endl;

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