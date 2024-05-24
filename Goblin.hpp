#pragma once
#include "NpCharacter.hpp"

class Goblin : public NpCharacter
{
public:
	//Constructor
	Goblin(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp);

	//Creator
	static Goblin* createEnemy(int enemyId);
};

