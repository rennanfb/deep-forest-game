#include "Saberwolf.hpp"

//Constructor

Saberwolf::Saberwolf(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

Saberwolf* Saberwolf::createEnemy()
{
	return new Saberwolf("Rabid Saberwolf", "Forest", "Beast", 22.0f, 22.0f, 20.0f, 18.0f, 20.0f, 140);

}

Bag* Saberwolf::createNpcBag()
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
		npcItems.push_back(PotionSmall::createItem());

		return new Bag(10, npcItems);
	}
	else
	{
		npcItems.push_back(ElixirSmall::createItem());
		npcItems.push_back(PotionMedium::createItem());
		return new Bag(10, npcItems);
	}

}

//Skills Sets

void Saberwolf::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	size_t target = chooseEnemy(players);

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
		this->bite(players[target]);
	}
	else if (chance >= 86 && chance <= 100)
	{
		this->clawStrike(players[target]);
	}

}