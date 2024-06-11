#include "BoarColossal.hpp"

//Constructor

BoarColossal::BoarColossal(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

BoarColossal* BoarColossal::createEnemy()
{
	return new BoarColossal("Colossal Boar", "Forest", "Boar", 18.0f, 8.0f, 30.0f, 3.0f, 30.0f, 160);

}

Bag* BoarColossal::createNpcBag()
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
		npcItems.push_back(ElixirLarge::createItem());
		return new Bag(10, npcItems);
	}

}

//Skills Sets

void BoarColossal::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 60)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 61 && chance < 80)
	{
		this->bite(players[target]);
	}
	else if (chance >= 81 && chance <= 100)
	{
		this->clawStrike(players[target]);
	}

}
