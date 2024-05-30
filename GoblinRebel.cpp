#include "GoblinRebel.hpp"

//Constructor

GoblinRebel::GoblinRebel(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

GoblinRebel* GoblinRebel::createEnemy()
{
	return new GoblinRebel("Rebel Goblin", "Street", "Goblin", 8.0f, 12.0f, 8.0f, 5.0f, 12.0f, 38);
}

//Skills Sets

void GoblinRebel::npcSkillSet(NpCharacter* npc, Character* player) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 50)
	{
		npc->basicAttack(player);
	}
	else if (chance >= 51 && chance < 80)
	{
		npc->throwDagger(player);
	}
	else if (chance >= 81 && chance <= 100)
	{
		npc->stockCharge(player);
	}

}