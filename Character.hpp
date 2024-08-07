#pragma once
#include "Creature.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

class Bag;
class Buff;
class Debuff;
class NpCharacter;

class Character : public Creature
{
public:

	Bag* bag;

protected:

	//Combat Stats

	float healthPoints = 0.0f;
	float attackPoints = 0.0f;
	float magicAttackPoints = 0.0f;
	float armor = 0.0f;
	float dodge = 0.0f;
	float precision = 0.0f;
	float criticalChance = 0.0f;

	//Experience

	int exp = 0;
	int level = 1;
	int nextLevelExp = 100;

	std::vector<Buff*> buffList;
	std::vector<Debuff*> debuffList;

public:

	//Constructor

	Character(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp);

	//Pure Virtual Methods

	virtual void showSheet() const = 0;
	virtual void showCombatLayout(std::vector <Character*> allies, std::vector<NpCharacter*> enemies) = 0;
	virtual void basicAttack(NpCharacter* enemy) = 0;
	virtual void healStats() = 0;
	virtual void upgradeAttributes() = 0;
	virtual void checkLevelAttributes() = 0;
	virtual void restoreEnergy(float energyAmount) = 0;
	virtual void decreaseEnergy(float energyAmount) = 0;
	virtual void calculateCombatStatus() = 0;

	//Combat Methods

	float calculateAverageDamage(float damage) const;
	float calculateAverageMagicDamage(float damage) const;
	std::vector<NpCharacter*> filterAliveEnemies(std::vector<NpCharacter*> enemies);
	std::vector<Character*> filterAliveAllies(std::vector<Character*> allies);
	int chooseEnemy(const std::vector<NpCharacter*>& enemies);
	int chooseAlly(const std::vector<Character*>& allies);
	void applyBuff(Buff* buff);
	void removeBuff(Buff* buff);
	void clearBuffs();
	void applyDebuff(Debuff* buff);
	void removeDebuff(Debuff* debuff);
	void clearDebuffs();
	float damageReduction() const override;
	void restoreHealth(float heal);
	virtual void decreaseHealth(float damage) override;
	bool dodgeAttack(NpCharacter* enemy) const;
	bool criticalHit() const; 
	bool isAlive() const;
	void defeatEnemy(NpCharacter* enemy);

	//Level Up Methods

	void levelUp();
	void verifyLvl();
	void increaseExp(NpCharacter* enemy);

	//Uppers

	void upNextLevelExp(int restExp);

	//Getters

	float getHealthPoints() const;
	float getAttackPoints() const;
	float getAverageAttackBase() const;
	float getMagicAttackPoints() const;
	float getAverageMagicAttackBase() const;
	float getArmor() const;
	float getPrecision() const;
	int getExp() const;
	int getLevel() const;
	int getNextLevelExp() const;
	std::vector<Buff*> getBuffList() const;
	std::vector<Debuff*> getDebuffList() const;
	bool isBuffed();
	bool isDebuffed();

	//Setters

	void setHealthPoints(float healthPoints);
	void setAttackPoints(float attackPoints);
	void setMagicAttackPoints(float magicAttackPoints);
	void setArmor(float armor);
	void setPrecision(float precision);
	void setExp(int exp);
	void setLevel(int level);
	void setNextLevelExp(int nextLevelExp);
};

