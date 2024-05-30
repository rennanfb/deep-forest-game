#include "GoblinWarrior.hpp"

//Constructor

GoblinWarrior::GoblinWarrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

GoblinWarrior* GoblinWarrior::createEnemy()
{
		return new GoblinWarrior("Warrior Gobnier", "Gobnier", "Goblin", 10.0f, 7.0f, 12.0f, 3.0f, 10.0f, 45);
	
}

//Skills Sets

void GoblinWarrior::npcSkillSet(NpCharacter* npc, Character* player) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 70)
	{
		npc->basicAttack(player);
	}
	else if (chance >= 71 && chance < 90)
	{
		npc->stockCharge(player);
	}
	else if (chance >= 91 && chance <= 100)
	{
		npc->spinningSlash(player);
	}

}