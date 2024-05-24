#include "NpCharacter.hpp"
#include "Character.hpp"

//Contructor 

NpCharacter::NpCharacter(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp) :
	Creature(name, faction, race),
	healthPoints(healthPoints),
	attackPoints(attackPoints),
	armor(armor),
	dodge(dodge),
	criticalChance(criticalChance),
	exp(exp)
{

}

//Combat Methods

int NpCharacter::damageReduction()
{
	int damageReduction = this->armor / 5;
	return damageReduction;
}

bool NpCharacter::dodgeAttack() 
{
	std::srand(std::time(nullptr));
	int chance = std::rand() % 100;
	if (chance < this->dodge) {
		std::cout << this->getName() << " dodges the enemy's attack" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool NpCharacter::criticalHit() 
{
	std::srand(std::time(nullptr));
	int chance = std::rand() % 100;
	if (chance < this->criticalChance) 
	{
		std::cout << this->getName() << " * Critical Damage * " << std::endl;
		return true;
	}
	else 
	{
		return false;
	}
}

void NpCharacter::decreaseHealth(int damage) 
{
	this->healthPoints -= damage;
}

bool NpCharacter::isAlive() {
	if (this->healthPoints > 0) {
		return true;
	}
	else
	{
		return false;
	}
}

void NpCharacter::basicAttack(Character* enemy) 
{
	if (enemy->dodgeAttack() != true) 
	{
		if (this->criticalHit() == true)
		{
			int criticalDamage = this->getAttackPoints() * 2;
			int damage = criticalDamage - enemy->damageReduction();

			std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}
		else
		{
			int damage = this->getAttackPoints() - enemy->damageReduction();
			std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}
	}
}

//Getters

int NpCharacter::getHealthPoints()
{
	return healthPoints;
}

int NpCharacter::getAttackPoints()
{
	return attackPoints;
}
int NpCharacter::getArmor()
{
	return armor;
}

int NpCharacter::getExp()
{
	return exp;
}

//Setters

void NpCharacter::setHealthPoints(int healthPoints)
{
	this->healthPoints = healthPoints;
}
void NpCharacter::setAttackPoints(int attackPoints)
{
	this->attackPoints = attackPoints;
}
void NpCharacter::setArmor(int armor)
{
	this->armor = armor;
}
