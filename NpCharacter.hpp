#pragma once
#include <random>
#include "Creature.hpp"
#include "Character.hpp"
#include "Bag.hpp"
#include "Item.hpp"

class Bag;
class Buff;
class Debuff;
class Character;

class NpCharacter : public Creature
{
public:

	Bag* bag;

protected:

	float healthPoints = 0.0f;
	float attackPoints = 0.0f;
	float magicAttackPoints = 0.0f;
	float armor = 0.0f;
	float dodge = 0.0f;
	float precision = 0.0f;
	float criticalChance = 0.0f;

	int exp = 0;

	std::vector<Buff*> buffList;
	std::vector<Debuff*> debuffList;

public:

	//Constructor

	NpCharacter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp);

	//Pure Virtual Methos

	virtual void npcSkillSet(std::vector <Character*> players) = 0;
	virtual Bag* createNpcBag() = 0;

	//Combat Methods

	float calculateAverageDamage(float damage) const;
	float calculateAverageMagicDamage(float damage) const;
	virtual void calculateCombatStatus();
	size_t chooseEnemy(const std::vector<Character*>& players);
	void applyBuff(Buff* buff);
	void removeBuff(Buff* buff);
	void clearBuffs();
	void applyDebuff(Debuff* buff);
	void removeDebuff(Debuff* debuff);
	void clearDebuffs();
	void restoreHealth(float heal);
	void decreaseHealth(float damage);
	bool dodgeAttack(Character* enemy) const;
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
	void bloodBait(Character* enemy);
	void shadowEmbrace(Character* enemy);
	void etherWave(Character* enemy);
	void crushingGravity(std::vector<Character*> enemies);

	//Getters

	float getHealthPoints() const;
	float getAttackPoints() const;
	float getAverageAttackBase() const;
	float getMagicAttackPoints() const;
	float getAverageMagicAttackBase() const;
	float getArmor() const;
	float getPrecision() const;
	int getExp() const;
	std::vector<Buff*> getBuffList() const;
	std::vector<Debuff*> getDebuffList() const;
	bool isBuffed();
	bool isDebuffed();

	//Setters

	void setHealthPoints(float healthPoints);
	void setAttackPoints(float attackPower);
	void setMagicAttackPoints(float magicAttackPower);
	void setArmor(float armor);
	void setPrecision(float precision);
};

