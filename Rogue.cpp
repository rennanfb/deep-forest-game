#include "Rogue.hpp"
#include "DebuffBleeding.hpp"

//Cosntructor

Rogue::Rogue(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float stamina) :
	Character(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp, level, nextLevelExp),
	stamina(stamina)
{
	calculateCombatStatus();
}

//Creator

Rogue* Rogue::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Rogue(name, faction, race, 14.0f, 16.0f, 14.0f, 5.0f, 16.0f, 16.0f, 0, 1, 100, 100.0f);
}

//Override Methods

void Rogue::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Rogue Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << " | Armor Power: " << getArmor() << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << " | M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Rogue::showCombatLayout(std::vector <Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{
		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "SP: " << this->getStamina();
		std::cout << std::endl;
		std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
		std::cout << " ------------ " << "Skills" << " ------------ " << std::endl;
		std::cout << "|1| - Basic Attack" << std::endl;
		std::cout << "|2| - Twin Blades (40SP)" << std::endl;
		std::cout << "|3| - Deep Wound (60SP)" << std::endl;
		std::cout << "|4| - Seven Sins (80SP)" << std::endl;
		std::cout << std::endl;

		std::cout << "--------------------------------" << std::endl;
		std::cout << "Possible Targets: " << std::endl;
		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i]->isAlive()) {
				std::cout << "- " << enemies[i]->getName() << " | HP: " << enemies[i]->getHealthPoints() << " | ATK: " << enemies[i]->getAttackPoints() << " | DEF: " << enemies[i]->getArmor() << std::endl;
			}
		}
		std::cout << "--------------------------------" << std::endl;
		std::cout << std::endl;

		std::cout << "* Enter the number of your next attack (1, 2, 3, 4) | or Enter (0) to access your bag *" << std::endl;

		int nextMove;
		std::cin >> nextMove;
		std::cout << std::endl;

		if (nextMove == 0)
		{
			this->bag->showBagLayout(this);
			this->showCombatLayout(allies, enemies);
		}
		else if (nextMove == 1)
		{
			int targetIndex = chooseEnemy(aliveEnemies);
			NpCharacter* target = aliveEnemies[targetIndex];

			this->basicAttack(target);
		}
		else if (nextMove == 2)
		{
			if (this->getStamina() >= 39.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->twinBlades(target);
			}
			else
			{
				std::cout << "Insufficient stamina, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 3)
		{
			if (this->getStamina() >= 59.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->deepWound(target);
			}
			else
			{
				std::cout << "Insufficient stamina, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 4)
		{
			if (this->getStamina() >= 79.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->sevenSins(target);
			}
			else
			{
				std::cout << "Insufficient stamina, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else
		{
			std::cout << "You must write the number of the skill options" << std::endl;
			this->showCombatLayout(allies, enemies);

		}
	}
	else
	{
		return;
	}
}


void Rogue::upgradeAttributes()
{
	this->upStrength(4.0f);
	this->upAgility(5.0f);
	this->upConstitution(3.0f);
	this->upIntelligence(2.0f);
	this->upDexterity(3.0f);
	this->upLucky(5.0f);
	calculateCombatStatus();
}

void Rogue::checkLevelAttributes()
{
	for (size_t i = 0; i < this->getLevel(); ++i)
	{
		this->upStrength(4.0f);
		this->upAgility(5.0f);
		this->upConstitution(3.0f);
		this->upIntelligence(2.0f);
		this->upDexterity(3.0f);
		this->upLucky(5.0f);
		this->nextLevelExp += 100;
	}
	calculateCombatStatus();
}

void Rogue::healStats()
{
	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->calculateStamina();
}

void Rogue::basicAttack(NpCharacter* target)
{
	std::cout << this->getName() << " attacked " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float criticalDamage = this->getAttackPoints() * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}


			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
		else
		{
			float averageDamage = calculateAverageDamage(this->getAttackPoints());
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseStamina();
		return;
	}
}

void Rogue::restoreEnergy(float energyAmount) 
{
	this->stamina += energyAmount;

	if (this->stamina > 100.0f + (this->getConstitution() / 3.0f))
	{
		this->calculateStamina();
	}
}

void Rogue::calculateCombatStatus()
{
	this->healthPoints = this->getConstitution() * 8.0f;
	this->attackPoints = this->getStrength() * 2.5f;
	this->magicAttackPoints = this->getIntelligence() * 2.0f;
	this->armor = this->getConstitution() * 2.0f;
	this->dodge = this->getAgility() / 1.5f;
	this->precision = this->getDexterity() / 1.5f;
	this->criticalChance = this->getLucky() / 1.5f;
}

//Combat Methods

void Rogue::calculateStamina()
{
	this->stamina = 100.0f + (this->getConstitution() / 3.0f);
}

void Rogue::increaseStamina() 
{
	this->stamina += 15.0f;
	std::cout << this->getName() << " breathes and regenerates 15 SP" << std::endl;

	if (this->stamina > 100.0f + (this->getConstitution() / 3.0f)) {
		this->calculateStamina();
	}
}


void Rogue::twinBlades(NpCharacter* target)
{
	this->stamina -= 40.0f;

	std::cout << this->getName() << " used Twin Blades against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 0.3f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 0.3f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseStamina();
		return;
	}
}

void Rogue::deepWound(NpCharacter* target)
{
	this->stamina -= 60.0f;

	std::cout << this->getName() << " used Deep Wound against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 0.5f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 0.5f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}

		Debuff* bleed = DebuffBleeding::create(this, target);
		target->applyDebuff(bleed);

	}
	else
	{
		this->increaseStamina();
		return;
	}

}

void Rogue::sevenSins(NpCharacter* target)
{
	this->stamina -= 80.0f;

	std::cout << this->getName() << " used Seven Sins against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 1.2f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 1.2f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseStamina();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseStamina();
		return;
	}
}

//Getters

float Rogue::getStamina() const
{
	return stamina;
}

//Setters

void Rogue::setStamina(float stamina)
{
	this->stamina = stamina;
}
