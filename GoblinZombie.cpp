#include "GoblinZombie.hpp"

//Constructor

GoblinZombie::GoblinZombie(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

GoblinZombie* GoblinZombie::createEnemy()
{
	return new GoblinZombie("Zombie Goblin", "Street", "Goblin", 8.0f, 10.0f, 6.0f, 2.0f, 7.0f, 20.0f, 35);

}

Bag* GoblinZombie::createNpcBag()
{
	std::vector<Item*> npcItems;
	return new Bag(10, npcItems);
}

//Skills Sets

void GoblinZombie::npcSkillSet(std::vector <Character*> players)
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