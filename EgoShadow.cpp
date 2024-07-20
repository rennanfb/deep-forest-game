#include "EgoShadow.hpp"

//Constructor

EgoShadow::EgoShadow(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

EgoShadow* EgoShadow::createEnemy()
{
	return new EgoShadow("Ego Shadow", "Unknown", "Unknown", 20.0f, 15.0f, 20.0f, 5.0f, 13.0f, 15.0f, 125);

}

Bag* EgoShadow::createNpcBag()
{
	std::vector<Item*> npcItems;
	return new Bag(10, npcItems);
}

//Skills Sets

void EgoShadow::npcSkillSet(std::vector <Character*> players)
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