#pragma once
#include "Creature.hpp"

class Character;

class NpCharacter : public Creature
{
private:
	int healthPoints;
	int attackPoints;
	int armor;
	int dodge;
	int criticalChance;
	int exp;
public:
	//Constructor
	NpCharacter(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance,int exp);

	//Combat Methods
	void decreaseHealth(int damage);
	bool dodgeAttack();
	bool criticalHit();
	int damageReduction();
	bool isAlive();
	void basicAttack(Character* enemy);

	//Getters
	int getHealthPoints();
	int getAttackPoints();
	int getArmor();
	int getExp();

	//Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPower);
	void setArmor(int armor);
};

