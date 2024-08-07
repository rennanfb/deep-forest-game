#include "InjuriedSeiren.hpp"

//Constructor

InjuriedSeiren::InjuriedSeiren(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

InjuriedSeiren* InjuriedSeiren::createEnemy()
{
	return new InjuriedSeiren("Injuried Seiren", "Unknown", "Elf", 30.0f, 25.0f, 77.0f, 40.0f, 28.0f, 25.0f, 631);

}

Bag* InjuriedSeiren::createNpcBag()
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

void InjuriedSeiren::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;
	std::cout << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 20)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 21 && chance < 60)
	{
		this->shadowEmbrace(players[target]);
	}
	else if (chance >= 61 && chance < 85)
	{
		this->crushingGravity(players);
	}
	else if (chance >= 86 && chance <= 100)
	{
		this->etherWave(players[target]);
	}

}