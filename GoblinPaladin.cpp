#include "GoblinPaladin.hpp"

//Constructor

GoblinPaladin::GoblinPaladin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, lucky, exp)
{
	calculateCombatStatus();
}

//Creator

GoblinPaladin* GoblinPaladin::createEnemy()
{
	return new GoblinPaladin("Paladin Gobnier", "Gobnier", "Goblin", 12.0f, 4.0f, 15.0f, 7.0f, 8.0f, 60);

}

//Skills Sets

void GoblinPaladin::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	int target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 75)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 76 && chance < 100)
	{
		this->shieldBash(players[target]);
	}

}