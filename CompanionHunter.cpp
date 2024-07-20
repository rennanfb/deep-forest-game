#include "CompanionHunter.hpp"

//Constructor

CompanionHunter::CompanionHunter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float focus) :
	Character(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp, level, nextLevelExp),
	focus(focus)
{
	calculateCombatStatus();
}

//Creator

CompanionHunter* CompanionHunter::createCharacter(std::string name, std::string faction, std::string race)
{
	return new CompanionHunter(name, faction, race, 5.0f, 20.0f, 17.0f, 10.0f, 30.0f, 20.0f, 0, 1, 100, 100.0f);
}

//Override Methods

void CompanionHunter::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Priest Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << " | Armor Power: " << getArmor() << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << " | M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void CompanionHunter::showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{
		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "FP: " << this->getFocus();
		std::cout << std::endl;
		std::cout << " --------- " << "Skills" << " --------- " << std::endl;
		std::cout << "|1| - Basic Attack" << std::endl;
		std::cout << "|2| - Double Shot (30MP)" << std::endl;
		std::cout << "|3| - Piercing Arrow (70MP)" << std::endl;
		std::cout << "|4| - Arrow Storm (100MP) (Target: All)" << std::endl;
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

		std::cout << "* Enter the number of your next attack (1, 2, 3, 4) or Enter (0) to access your bag " << std::endl;
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
			if (this->getFocus() >= 29.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->doubleShot(allies, enemies, target);
			}
			else
			{
				std::cout << "Insufficient focus, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 3)
		{
			if (this->getFocus() >= 69.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->piercingArrow(allies, enemies, target);
			}
			else
			{
				std::cout << "Insufficient focus, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 4)
		{
			if (this->getFocus() >= 99.5f)
			{
				this->arrowStorm(allies, aliveEnemies);
			}
			else
			{
				std::cout << "Insufficient focus, select a possible move" << std::endl;
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

void CompanionHunter::upgradeAttributes()
{
	this->upStrength(1.0f);
	this->upAgility(3.0f);
	this->upConstitution(2.0);
	this->upIntelligence(3.0);
	this->upDexterity(5.0f);
	this->upLucky(3.0);
	calculateCombatStatus();
}

void CompanionHunter::healStats()
{

	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setFocus(this->getDexterity() * 5.0f);

}

void CompanionHunter::basicAttack(NpCharacter* target)
{
	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float criticalDamage = this->getAttackPoints() * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " attacked " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
			this->increaseFocus();
			std::cout << std::endl;
		}
		else
		{
			float averageDamage = calculateAverageDamage(this->getAttackPoints());
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " attacked " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseFocus();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseFocus();
		return;
	}
}

void CompanionHunter::restoreEnergy(float energyAmount)
{
	this->focus += energyAmount;

	if (this->focus > 100.0f + (getDexterity() * 2.0f))
	{
		this->calculateFocus();
	}
}

void CompanionHunter::calculateCombatStatus()
{
	this->healthPoints = this->getConstitution() * 6.0f;
	this->attackPoints = this->getDexterity() * 2.0f;
	this->magicAttackPoints = this->getIntelligence() * 1.5f;
	this->armor = this->getConstitution() * 3.0f;
	this->dodge = this->getAgility() / 1.3f;
	this->precision = this->getStrength() / 2.0f;
	this->criticalChance = this->getLucky() / 1.8f;
}

//Combat Methods

void CompanionHunter::calculateFocus()
{
	this->focus = 100.0f + (getDexterity() * 2.0f);
}

void CompanionHunter::increaseFocus()
{
	this->focus += 10;
	std::cout << this->getName() << " concentrates and recovered 10FP" << std::endl;

	if (this->focus > 100.0f + (getDexterity() * 2.0f))
	{
		this->calculateFocus();
	}
}

void CompanionHunter::doubleShot(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	this->focus -= 30;


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
			std::cout << this->getName() << " used Double Shot against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
			this->increaseFocus();
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
			std::cout << this->getName() << " used Double Shot against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseFocus();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseFocus();
		return;
	}
}

void CompanionHunter::piercingArrow(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	this->focus -= 60;

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
			std::cout << this->getName() << " used Piercing Arrow against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
			this->increaseFocus();
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
			std::cout << this->getName() << " used Piercing Arrow against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseFocus();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseFocus();
		return;
	}

}

void CompanionHunter::arrowStorm(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	this->focus -= 100;

	if (this->criticalHit())
	{
		float skillDamageBonus = this->getMagicAttackPoints() * 0.7f;
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
			}
		}

		std::cout << this->getName() << " used Arrow Storm, causing " << damage << " points of area damage" << std::endl;
		this->increaseFocus();
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
			}
		}

		std::cout << this->getName() << " used Arrow Storm, causing " << damage << " points of area damage" << std::endl;
		this->increaseFocus();
		std::cout << std::endl;
	}

}

//Getters

float CompanionHunter::getFocus() const
{
	return focus;
}

//Setters

void CompanionHunter::setFocus(float mana)
{
	this->focus = mana;
}