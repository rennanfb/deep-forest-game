#include "Mage.hpp"

//Constructor

Mage::Mage(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float mana) :
	Character(name, faction, race, strength, agility, constitution, intelligence, lucky, exp, level, nextLevelExp),
	mana(mana)
{
	calculateCombatStatus();
}

//Creator

Mage* Mage::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Mage(name, faction, race, 5.0f, 5.0f, 12.0f, 20.0f, 13.0f, 0, 1, 100, 100.0);
}

//Override Methods

void Mage::showSheet() const 
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Mage Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << " | Armor Power: " << getArmor() << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << " | M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Mage::showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{
		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "MP: " << this->getMana();
		std::cout << std::endl;
		std::cout << " ------------ " << "Skills" << " ------------ " << std::endl;
		std::cout << "|1| - Basic Attack" << std::endl;
		std::cout << "|2| - Fire Ball (30MP)" << std::endl;
		std::cout << "|3| - Earthquake (60MP) (Target: all enemies)" << std::endl;
		std::cout << "|4| - Cloud Strife (90MP)" << std::endl;
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

		std::cout << "* Enter the number of your next attack (1, 2, 3, 4) or Enter (0) to access your bag *" << std::endl;
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
			if (this->getMana() >= 29.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->fireBall(target);
			}
			else
			{
				std::cout << "Insufficient mana, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 3)
		{
			if (this->getMana() >= 59.5f)
			{
				this->earthQuake(enemies);
			}
			else
			{
				std::cout << "Insufficient mana, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 4)
		{
			if (this->getMana() >= 89.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->cloudStrife(target);
			}
			else
			{
				std::cout << "Insufficient mana, select a possible move" << std::endl;
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

void Mage::upgradeAttributes()
{
	this->upStrength(2.0f);
	this->upAgility(2.0f);
	this->upConstitution(3.0);
	this->upIntelligence(6.0);
	this->upLucky(3.0);
	calculateCombatStatus();
}

void Mage::healStats()
{

	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setMana(this->getIntelligence() * 5.0f);

}

void Mage::basicAttack(NpCharacter* target)
{
	if (!target->dodgeAttack())
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
			std::cout << this->getName() << " attacked " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
			this->increaseMana();
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
			std::cout << this->getName() << " attacked " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
		}
	}
	else 
	{
		this->increaseMana();
		return;
	}
}

void Mage::restoreEnergy(float energyAmount)
{
	this->mana += energyAmount;

	if (this->mana > getIntelligence() * 5.0f)
	{
		this->setMana(getIntelligence() * 5.0f);
	}
}

//Combat Methods

void Mage::calculeMana() 
{
	this->mana = getIntelligence() * 5.0f;
}

void Mage::increaseMana() 
{
	this->mana += 10.0f;
	std::cout << this->getName() << " meditated and recovered 10MP" << std::endl;

	if (this->mana > getIntelligence() * 5.0f) 
	{
		this->setMana(getIntelligence() * 5.0f);
	}
}

void Mage::fireBall(NpCharacter* target)
{
	this->mana -= 30;

	if (!target->dodgeAttack())
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Fire Ball against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageMagicDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Fire Ball against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
			}
		}
	else
	{
		this->increaseMana();
		return;
	}
}

void Mage::earthQuake(std::vector<NpCharacter*> enemies)
{
	this->mana -= 60;

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
			if (!enemies[i]->dodgeAttack())
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
			}
		}

		std::cout << this->getName() << " used Earthquake, causing " << damage << " points of area damage" << std::endl;
		this->increaseMana();
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
			if (!enemies[i]->dodgeAttack())
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
			}
		}

		std::cout << this->getName() << " used Earthquake, causing " << damage << " points of area damage" << std::endl;
		this->increaseMana();
		std::cout << std::endl;
	}
}

void Mage::cloudStrife(NpCharacter* target)
{
	this->mana -= 90;

	if (!target->dodgeAttack())
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 1.5f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Cloud Strife against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 1.5f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageMagicDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Cloud Strife against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
		}
	}
	else
	{
		this->increaseMana();
		return;
	}
}

//Getters

float Mage::getMana() const
{
	return mana;
}

//Setters

void Mage::setMana(float mana)
{
	this->mana = mana;
}