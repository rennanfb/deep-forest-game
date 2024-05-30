#pragma once
#include "Creature.hpp"
#include "Character.hpp"
#include <random>

class Character;

class NpCharacter : public Creature
{
private:
	float healthPoints;
	float attackPoints;
	float magicAttackPoints;
	float armor;
	float dodge;
	float criticalChance;
	int exp;
public:

	//Constructor

	NpCharacter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Pure Virtual Methos

	virtual void npcSkillSet(NpCharacter* npc, Character* player) = 0;

	//Combat Methods

	float calculateAverageDamage(float damage);
	float calculateAverageMagicDamage(float damage);
	virtual void calculateCombatStatus();
	void decreaseHealth(float damage);
	bool dodgeAttack() const;
	bool criticalHit() const;
	float damageReduction() const;
	bool isAlive() const;
	void basicAttack(Character* enemy);

	//Skills Methods

	void bite(Character* enemy);
	void clawStrike(Character* enemy);
	void throwDagger(Character* enemy);
	void stockCharge(Character* enemy);
	void spinningSlash(Character* enemy);
	void shieldBash(Character* enemy);
	void shadowEmbrace(Character* enemy);

	//Getters

	float getHealthPoints() const;
	float getAttackPoints() const;
	float getAverageAttackBase() const;
	float getMagicAttackPoints() const;
	float getAverageMagicAttackBase() const;
	float getArmor() const;
	int getExp() const;

	//Setters

	void setHealthPoints(float healthPoints);
	void setAttackPoints(float attackPower);
	void setMagicAttackPoints(float magicAttackPower);
	void setArmor(float armor);
};

