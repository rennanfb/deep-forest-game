#include "NpCharacter.hpp"

//Contructor 

NpCharacter::NpCharacter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp) :
	Creature(name, faction, race, strength, agility, constitution, intelligence, lucky),
	exp(exp)
{
	calculateCombatStatus();
}

//Combat Methods

float NpCharacter::calculateAverageDamage(float damage)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1.0f, 5.0f);

	float averageDamageBonus = this->getAverageAttackBase();

	std::uniform_int_distribution<> disMinMax(1, 2);

	int damageUpOrDownChance = disMinMax(gen);
	if (damageUpOrDownChance == 1)
	{
		damage -= averageDamageBonus;
	}
	else
	{
		damage += averageDamageBonus;
	}
	return damage;
}

float NpCharacter::calculateAverageMagicDamage(float damage)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(1.0f, 5.0f);

	float averageDamageBonus = this->getAverageMagicAttackBase();

	std::uniform_int_distribution<> disMinMax(1, 2);

	int damageUpOrDownChance = disMinMax(gen);
	if (damageUpOrDownChance == 1)
	{
		damage -= averageDamageBonus;
	}
	else
	{
		damage += averageDamageBonus;
	}
	return damage;
}

void NpCharacter::calculateCombatStatus()
{
	this->healthPoints = this->getConstitution() * 10.0f;
	this->attackPoints = this->getStrength() * 2.0f;
	this->magicAttackPoints = this->getIntelligence() * 2.0f;
	this->armor = this->getConstitution() * 3.0f;
	this->dodge = this->getAgility() / 2.0f;
	this->criticalChance = this->getLucky() / 2.0f;
}

size_t NpCharacter::chooseEnemy(const std::vector<Character*>& enemies) 
{
	if (enemies.size() > 0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dis(0, enemies.size() - 1);

		size_t target = dis(gen);

		return target;
	}
	else
	{
		return 0;
	}

}

float NpCharacter::damageReduction() const
{
	float damageReduction = this->armor / 5.0f;
	return damageReduction;
}

bool NpCharacter::dodgeAttack() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance < this->dodge) {
		std::cout << this->getName() << " dodges the attack" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool NpCharacter::criticalHit() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

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

void NpCharacter::decreaseHealth(float damage)
{
	this->healthPoints -= damage;
}

bool NpCharacter::isAlive() const 
{
	if (this->healthPoints > 1.0f) {
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
			float criticalDamage = this->getAttackPoints() * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}
			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float averageDamage = calculateAverageDamage(this->getAttackPoints());
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

//Skills Methods

void NpCharacter::bite(Character* enemy) 
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 0.2f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Bite against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 0.2f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Bite against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}
void NpCharacter::clawStrike(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 0.3f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Claw Strike against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 0.3f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Claw Strike against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::throwDagger(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 0.4f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Throw Dagger against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 0.4f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Throw Dagger against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::stockCharge(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 0.6f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Stock Charge against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 0.6f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Stock Charge against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::spinningSlash(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 0.8f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Spinning Slash against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 0.8f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Spinning Slash against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::shieldBash(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{
			float skillDamageBonus = this->getAttackPoints() * 1.0f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Shield Bash against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getAttackPoints() * 1.0f;
			float skillDamage = bonusDamage += this->getAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Shield Bash against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::shadowEmbrace(Character* enemy)
{
	if (enemy->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
		{

			float skillDamageBonus = this->getMagicAttackPoints() * 1.3f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Shadow Embrace against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getMagicAttackPoints() * 1.3f;
			float skillDamage = bonusDamage += this->getMagicAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << this->getName() << " used Shadow Embrace against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}


//Getters

float NpCharacter::getHealthPoints() const
{
	return healthPoints;
}

float NpCharacter::getAttackPoints() const
{
	return attackPoints;
}

float NpCharacter::getAverageAttackBase() const
{
	float averageAttackBase = this->attackPoints * 0.1f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, averageAttackBase);

	float averageDamage = dis(gen);
	return averageDamage;

}

float NpCharacter::getMagicAttackPoints() const
{
	return magicAttackPoints;
}

float NpCharacter::getAverageMagicAttackBase() const
{
	float averageMagicAttackBase = this->magicAttackPoints * 0.1f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, averageMagicAttackBase);

	float averageMagicDamage = dis(gen);
	return averageMagicDamage;
}

float NpCharacter::getArmor() const
{
	return armor;
}

int NpCharacter::getExp() const
{
	return exp;
}

//Setters

void NpCharacter::setHealthPoints(float healthPoints)
{
	this->healthPoints = healthPoints;
}
void NpCharacter::setAttackPoints(float attackPoints)
{
	this->attackPoints = attackPoints;
}
void NpCharacter::setMagicAttackPoints(float magicAttackPoints)
{
	this->magicAttackPoints = magicAttackPoints;
}
void NpCharacter::setArmor(float armor)
{
	this->armor = armor;
}
