#include "GnomeRath.hpp"

//Constructor

GnomeRath::GnomeRath(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

GnomeRath* GnomeRath::createEnemy()
{
	return new GnomeRath("Rath", "Street", "Gnome", 17.0f, 20.0f, 15.0f, 5.0f, 10.0f, 90);

}

//Skills Sets

void GnomeRath::npcSkillSet(NpCharacter* npc, Character* player) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 70)
	{
		npc->basicAttack(player);
	}
	else if (chance >= 71 && chance < 100)
	{
		npc->shieldBash(player);
	}

}