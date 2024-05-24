#pragma once
#include "Creature.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

class NpCharacter;

class Character : public Creature
{
protected:
	int healthPoints;
	int attackPoints;
	int armor;
	int dodge;
	int criticalChance;
	int exp;
	int level;
	int nextLevelExp;
public:
	//Constructor
	Character(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge,int criticalChance, int exp, int level, int nextLevelExp);

	//Pure Virtual Methods
	virtual void showSheet() = 0;
	virtual void showCombatLayout(NpCharacter* enemy) = 0;
	virtual void basicAttack(NpCharacter* enemy) = 0;
	virtual void healStats() = 0;
	virtual void upgradeAttributes() = 0;

	//Combat Methods
	int damageReduction();
	virtual void decreaseHealth(int damage);
	bool dodgeAttack();
	bool criticalHit();
	bool isAlive();

	//Level Up Methods
	void levelUp();
	void verifyLvl();
	void increaseExp(NpCharacter* enemy);

	//Uppers
	void upHealthPoints(int upgrade);
	void upAttackPoints(int upgrade);
	void upArmor(int upgrade);

	//Getters
	int getHealthPoints();
	int getAttackPoints();
	int getArmor();
	int getExp();
	int getLevel();
	int getNextLevelExp();

	//Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPower);
	void setArmor(int armor);
	void upNextLevelExp(int restExp);
	void setExp(int exp);
	void setLevel(int level);
	void setnextLevelExp(int nextLevelExp);
};

