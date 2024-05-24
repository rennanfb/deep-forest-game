#include "Goblin.hpp"

//Constructor

Goblin::Goblin(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp) :
	NpCharacter(name, faction, race, healthPoints, attackPoints, armor, dodge, criticalChance, exp) 
{

}

//Creator

Goblin* Goblin::createEnemy(int enemyId) 
{
	if (enemyId == 1) 
	{
		return new Goblin("Rebel Goblin", "Street", "Goblin", 80, 20, 15, 10, 10, 38);
	}
	else if (enemyId == 2) 
	{
		return new Goblin("Warrior Gobnier", "Gobnier", "Goblin", 150, 18, 25, 8, 8, 45);
	}
	else if (enemyId == 3) 
	{
		return new Goblin("Paladin Gobnier", "Gobnier", "Goblin", 180, 20, 35, 2, 5, 60);
	}
	else if (enemyId == 4) 
	{
		return new Goblin("Torturer Zulmin", "Gobnier", "Goblin", 220, 22, 35, 10, 15, 85);
	}
	else if (enemyId == 5)
	{
		return new Goblin("Zombie Goblin", "Street", "Goblin", 60, 25, 15, 5, 10, 35);
	}
}