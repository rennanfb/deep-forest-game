#include "NpCharacter.hpp"
#include "Buff.hpp"
#include "DebuffBurning.hpp"
#include "DebuffBleeding.hpp"
#include "DebuffPoisoned.hpp"
#include "DebuffStunned.hpp"
#include "FindBuffIndexByName.hpp"
#include "FindDebuffIndexByName.hpp"

//Contructor 

NpCharacter::NpCharacter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	Creature(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky),
	exp(exp)
{
	calculateCombatStatus();
}

//Combat Methods

float NpCharacter::calculateAverageDamage(float damage) const
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

float NpCharacter::calculateAverageMagicDamage(float damage) const
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
	this->precision = this->getDexterity() / 2.0f;
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

void NpCharacter::applyBuff(Buff* buff)
{
	for (const auto& it : buffList)
	{
		if (it->getName() == buff->getName())
		{
			it->restartDuration();
			return;
		}
	}

	this->buffList.push_back(buff);
}

void NpCharacter::removeBuff(Buff* buff)
{
	int buffIndex = FindBuffIndexByName(this->buffList, buff->getName());

	if (buffIndex != -1 && this->buffList[buffIndex]->getDuration() == 0)
	{
		this->buffList.erase(this->buffList.begin() + buffIndex);
	}
}

void NpCharacter::clearBuffs()
{
	for (auto buff : buffList)
	{
		delete buff;
	}
	buffList.clear();
}

void NpCharacter::applyDebuff(Debuff* debuff)
{
	for (const auto& it : debuffList)
	{
		if (it->getName() == debuff->getName())
		{
			it->restartDuration();
			return;
		}
	}

	this->debuffList.push_back(debuff);

}

void NpCharacter::removeDebuff(Debuff* debuff)
{
	int debuffIndex = FindDebuffIndexByName(this->debuffList, debuff->getName());

	if (debuffIndex != -1 && this->debuffList[debuffIndex]->getDuration() == 0)
	{
		this->debuffList.erase(this->debuffList.begin() + debuffIndex);
	}
}

void NpCharacter::clearDebuffs()
{
	for (auto debuff : debuffList)
	{
		delete debuff;
	}

	debuffList.clear();
}

float NpCharacter::damageReduction() const
{
	float damageReduction = this->armor / 5.0f;
	return damageReduction;
}

bool NpCharacter::dodgeAttack(Character* enemy) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(1, 100);

	float chance = dis(gen);

	chance += enemy->getPrecision() / 2;


	if (chance < this->dodge) 
	{
		std::cout << this->getName() << " dodges the attack" << std::endl;
		return true;
	}
	else 
	{
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
		std::cout << " * Critical Damage * " << std::endl;
		return true;
	}
	else 
	{
		return false;
	}
}

void NpCharacter::restoreHealth(float heal)
{
	std::cout << this->getName() << " received " << heal << " health points!" << std::endl;

	this->healthPoints += heal;
	if (this->healthPoints > this->getConstitution() * 10.0f)
	{
		this->healthPoints = this->getConstitution() * 10.0f;
	}

}

void NpCharacter::decreaseHealth(float damage)
{
	this->healthPoints -= damage;
	std::cout << this->getName() << " received " << damage << " points of damage!" << std::endl;
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
	std::cout << this->getName() << " attacked " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this)) 
	{
		if (this->criticalHit())
		{
			float criticalDamage = this->getAttackPoints() * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}
			enemy->decreaseHealth(damage);
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
	std::cout << this->getName() << " used Bite against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
	std::cout << this->getName() << " used Claw Strike against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
	std::cout << this->getName() << " used Throw Dagger against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
			std::cout << std::endl;
		}

		Debuff* poison = DebuffPoisoned::create(this, enemy);
		enemy->applyDebuff(poison);

	}
	else
	{
		return;
	}
}

void NpCharacter::stockCharge(Character* enemy)
{
	std::cout << this->getName() << " used Stock Charge against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
			std::cout << std::endl;
		}

		Debuff* bleed = DebuffBleeding::create(this, enemy);
		enemy->applyDebuff(bleed);

	}
	else
	{
		return;
	}
}

void NpCharacter::spinningSlash(Character* enemy)
{
	std::cout << this->getName() << " used Spinning Slash against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
	std::cout << this->getName() << " used Shield Bash against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::bloodBait(Character* enemy)
{
	std::cout << this->getName() << " used Blood Bait against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
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

			float healDamage = damage / 2;

			this->restoreHealth(healDamage);
			std::cout << this->getName() << " restored " << healDamage << " points of health" << std::endl;

			enemy->decreaseHealth(damage);
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

			float healDamage = damage / 2;

			this->restoreHealth(healDamage);
			std::cout << this->getName() << " restored " << healDamage << " points of health" << std::endl;

			enemy->decreaseHealth(damage);
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
	std::cout << this->getName() << " used Shadow Embrace against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
		{

			float skillDamageBonus = this->getMagicAttackPoints() * 1.0f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getMagicAttackPoints() * 1.0f;
			float skillDamage = bonusDamage += this->getMagicAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}

		Debuff* stun = DebuffStunned::create(this, enemy);
		enemy->applyDebuff(stun);
	}
	else
	{
		return;
	}
}

void NpCharacter::etherWave(Character* enemy)
{
	std::cout << this->getName() << " used Ether Wave against " << enemy->getName() << std::endl;

	if (!enemy->dodgeAttack(this))
	{
		if (this->criticalHit())
		{

			float skillDamageBonus = this->getMagicAttackPoints() * 1.5f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - enemy->damageReduction();

			float energyDrain = damage / 5;

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			std::cout << enemy->getName() << " had lost " << energyDrain << " points of energy" << std::endl;
			enemy->decreaseEnergy(energyDrain);
			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}
		else
		{
			float bonusDamage = this->getMagicAttackPoints() * 1.5f;
			float skillDamage = bonusDamage += this->getMagicAttackPoints();
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - enemy->damageReduction();

			float energyDrain = damage / 5;

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			std::cout << enemy->getName() << " had lost " << energyDrain << " points of energy" << std::endl;
			enemy->decreaseEnergy(energyDrain);
			enemy->decreaseHealth(damage);
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void NpCharacter::crushingGravity(std::vector<Character*> enemies)
{

	std::cout << this->getName() << " used Crushing Gravity " << std::endl;

	if (this->criticalHit())
	{
		float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
		float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
		float criticalDamage = skillDamage * 2.0f;
		float damage = calculateAverageMagicDamage(criticalDamage);

		if (damage < 0.0f)
		{
			damage = 0.0f;
		}

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack(this))
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(1, 100);

				int chance = dis(gen);
				if (chance < 30)
				{
					Debuff* stun = DebuffStunned::create(this, enemies[i]);
					enemies[i]->applyDebuff(stun);
				}
			}
		}
		std::cout << std::endl;
	}
	else
	{
		float skillDamageBonus = this->getMagicAttackPoints() * 0.7f;
		float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
		float damage = calculateAverageMagicDamage(skillDamage);

		if (damage < 0.0f)
		{
			damage = 0.0f;
		}

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack(this))
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());

				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(1, 100);

				int chance = dis(gen);
				if (chance < 30)
				{
					Debuff* stun = DebuffStunned::create(this, enemies[i]);
					enemies[i]->applyDebuff(stun);
				}
			}
		}
		std::cout << std::endl;
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

float NpCharacter::getPrecision() const
{
	return precision;
}

int NpCharacter::getExp() const
{
	return exp;
}

std::vector<Buff*> NpCharacter::getBuffList() const
{
	return buffList;
}

std::vector<Debuff*> NpCharacter::getDebuffList() const
{
	return debuffList;
}

bool NpCharacter::isBuffed()
{
	if (this->buffList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool NpCharacter::isDebuffed()
{
	if (this->debuffList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
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
void NpCharacter::setPrecision(float precision)
{
	this->precision = precision;
}
