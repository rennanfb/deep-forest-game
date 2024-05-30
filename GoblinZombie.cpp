#include "GoblinZombie.hpp"

//Constructor

GoblinZombie::GoblinZombie(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

GoblinZombie* GoblinZombie::createEnemy()
{
	return new GoblinZombie("Zombie Goblin", "Street", "Goblin", 8.0f, 10.0f, 6.0f, 2.0f, 20.0f, 35);

}

//Skills Sets

void GoblinZombie::npcSkillSet(NpCharacter* npc, Character* player) 
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
		npc->bite(player);
	}
	else if (chance >= 81 && chance <= 100)
	{
		npc->clawStrike(player);
	}

}