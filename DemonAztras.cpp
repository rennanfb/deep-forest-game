#include "DemonAztras.hpp"

//Constructor

DemonAztras::DemonAztras(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

DemonAztras* DemonAztras::createEnemy()
{
	return new DemonAztras("Aztras", "Unknown", "Demon", 25.0f, 20.0f, 25.0f, 20.0f, 20.0f, 125);
}

//Skills Sets

void DemonAztras::npcSkillSet(NpCharacter* npc, Character* player)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 60)
	{
		npc->basicAttack(player);
	}
	else if (chance >= 61 && chance < 80)
	{
		npc->shadowEmbrace(player);
	}
	else if (chance >= 81 && chance <= 100)
	{
		npc->clawStrike(player);
	}

}