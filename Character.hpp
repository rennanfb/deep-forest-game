#pragma once
#include "Creature.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

class NpCharacter;

class Character : public Creature
{
protected:

	//Combat Stats

	float healthPoints;
	float attackPoints;
	float magicAttackPoints;
	float armor;
	float dodge;
	float criticalChance;

	//Experience

	int exp;
	int level;
	int nextLevelExp;

public:
	//Constructor
	Character(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp);

	//Pure Virtual Methods
	virtual void showSheet() const = 0;
	virtual void showCombatLayout(std::vector<NpCharacter*> enemies) = 0;
	virtual void basicAttack(NpCharacter* enemy) = 0;
	virtual void healStats() = 0;
	virtual void upgradeAttributes() = 0;

	//Combat Methods

	float calculateAverageDamage(float damage);
	float calculateAverageMagicDamage(float damage);
	std::vector<NpCharacter*> filterAliveEnemies(std::vector<NpCharacter*> enemies);
	int chooseEnemy(const std::vector<NpCharacter*>& enemies);
	float damageReduction() const;
	void increaseHealth(float heal);
	virtual void decreaseHealth(float damage);
	bool dodgeAttack() const;
	bool criticalHit() const; 
	bool isAlive() const;

	//Level Up Methods
	void levelUp();
	void verifyLvl();
	void increaseExp(NpCharacter* enemy);

	//Uppers

	void calculateCombatStatus();
	void upNextLevelExp(int restExp);

	//Getters

	float getHealthPoints() const;
	float getAttackPoints() const;
	float getAverageAttackBase() const;
	float getMagicAttackPoints() const;
	float getAverageMagicAttackBase() const;
	float getArmor() const;
	int getExp() const;
	int getLevel() const;
	int getNextLevelExp() const;

	//Setters
	void setHealthPoints(float healthPoints);
	void setAttackPoints(float attackPoints);
	void setMagicAttackPoints(float magicAttackPoints);
	void setArmor(float armor);
	void setExp(int exp);
	void setLevel(int level);
	void setNextLevelExp(int nextLevelExp);
};

