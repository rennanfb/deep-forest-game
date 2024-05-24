#include "Character.hpp"
#include "NpCharacter.hpp"

//Constructor

Character::Character(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp) :
	Creature(name, faction, race),
	healthPoints(healthPoints),
	attackPoints(attackPoints),
	armor(armor),
	dodge(dodge),
	criticalChance(criticalChance),
	exp(exp),
	level(level),
	nextLevelExp(nextLevelExp)
{

}

//Combat Methods

int Character::damageReduction()
{
	int damageReduction = this->armor / 5;
	return damageReduction;
}

bool Character::dodgeAttack()
{
	std::srand(std::time(nullptr));
	int chance = std::rand() % 100;
	if (chance < this->dodge) {
		std::cout << this->getName() << " dodges the attack" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool Character::criticalHit()
{
	std::srand(std::time(nullptr));
	int chance = std::rand() % 100;
	if (chance < this->criticalChance) {
		std::cout << this->getName() << " * Critical Damage * " << std::endl;
		return true;
	}
	else {
		return false;
	}
}

void Character::decreaseHealth(int damage)
{
	this->healthPoints -= damage;
}

bool Character::isAlive() {
	if (this->healthPoints > 0) {
		return true;
	}
	else
	{
		return false;
	}
}

//Level Up Methods

void Character::levelUp()
{
	this->level++;
	this->upgradeAttributes();
	std::cout << std::endl;
	std::cout << "+ " << this->getName() << " Level up : " << this->getLevel() << "  +" << std::endl;
	if (this->exp > this->getNextLevelExp())
	{
		int expRest = exp -= this->getNextLevelExp();

		this->upNextLevelExp(expRest);
	}
	else
	{
		this->setExp(0);
	}
}


void Character::verifyLvl()
{
	if (this->exp >= this->nextLevelExp)
	{
		this->levelUp();
	}
}

void Character::increaseExp(NpCharacter* enemy)
{
	std::cout << this->getName() << " gained " << enemy->getExp() << " experience points" << std::endl;
	this->exp += enemy->getExp();
	this->verifyLvl();
}

//Uppers

void Character::upHealthPoints(int upgrade)
{
	this->healthPoints += upgrade;
}

void Character::upAttackPoints(int upgrade)
{
	this->attackPoints += upgrade;
}

void Character::upArmor(int upgrade)
{
	this->armor += upgrade;
}

void Character::upNextLevelExp(int restExp)
{
	this->setExp(restExp);
	this->nextLevelExp += 100;
}



//Getters

int Character::getHealthPoints() 
{
	return healthPoints;
}

int Character::getAttackPoints() 
{
	return attackPoints;
}
int Character::getArmor() 
{
	return armor;
}

int Character::getExp() 
{
	return exp;
}
int Character::getLevel()
{
	return level;
}
int Character::getNextLevelExp() 
{
	return nextLevelExp;
}

//Setters

void Character::setHealthPoints(int healthPoints) 
{
	this->healthPoints = healthPoints;
}
void Character::setAttackPoints(int attackPoints) 
{
	this->attackPoints = attackPoints;
}
void Character::setArmor(int armor) 
{
	this->armor = armor;
}

void Character::setExp(int exp) 
{
	this->exp = exp;
}
void Character::setLevel(int level) 
{
	this->level = level;
}
void Character::setnextLevelExp(int nextLevelExp) 
{
	this->nextLevelExp = nextLevelExp;
}

