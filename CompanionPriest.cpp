#include "CompanionPriest.hpp"

//Constructor

CompanionPriest::CompanionPriest(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float mana) :
	Character(name, faction, race, strength, agility, constitution, intelligence, lucky, exp, level, nextLevelExp),
	mana(mana)
{
	calculateCombatStatus();
}

//Creator

CompanionPriest* CompanionPriest::createCharacter(std::string name, std::string faction, std::string race)
{
	return new CompanionPriest(name, faction, race, 5.0f, 5.0f, 15.0f, 20.0f, 5.0f, 0, 1, 100, 100.0f);
}

//Override Methods

void CompanionPriest::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Priest Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void CompanionPriest::showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{
		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "MP: " << this->getMana();
		std::cout << std::endl;
		std::cout << " --------- " << "Skills" << " --------- " << std::endl;
		std::cout << "1 - Basic Attack" << std::endl;
		std::cout << "2 - Holy Light (30MP)" << std::endl;
		std::cout << "3 - Heal (60MP) (Target: Ally)" << std::endl;
		std::cout << "4 - Saviour Rain (90MP) (Target: All)" << std::endl;
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

		std::cout << "*Type the number of your next attack (1, 2, 3, 4)*" << std::endl;
		int nextMove;
		std::cin >> nextMove;
		std::cout << std::endl;

		if (nextMove == 1)
		{
			int targetIndex = chooseEnemy(aliveEnemies);
			NpCharacter* target = aliveEnemies[targetIndex];

			this->basicAttack(target);
		}
		else if (nextMove == 2)
		{
			if (this->getMana() >= 30)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->holyLight(allies, enemies, target);
			}
			else
			{
				std::cout << "Insufficient mana, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 3)
		{
			if (this->getMana() >= 60)
			{
				std::vector<Character*> aliveAllies = filterAliveAllies(allies);

				int targetIndex = chooseAlly(aliveAllies);
				Character* target = aliveAllies[targetIndex];

				this->heal(allies, enemies, target);
			}
			else
			{
				std::cout << "Insufficient mana, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 4)
		{
			if (this->getMana() >= 90)
			{
				std::vector<Character*> aliveAllies = filterAliveAllies(allies);
				this->saviourRain(aliveAllies, aliveEnemies);
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

void CompanionPriest::upgradeAttributes()
{
	this->upStrength(2.0f);
	this->upAgility(2.0f);
	this->upConstitution(4.0);
	this->upIntelligence(5.0);
	this->upLucky(3.0);
	calculateCombatStatus();
}

void CompanionPriest::healStats()
{

	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setMana(this->getIntelligence() * 5.0f);

}

void CompanionPriest::basicAttack(NpCharacter* target)
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
				damage = 0;
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
				damage = 0;
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

void CompanionPriest::restoreEnergy(float energyAmount)
{
	this->mana += energyAmount;

	if (this->mana > getIntelligence() * 5.0f)
	{
		this->setMana(getIntelligence() * 5.0f);
	}
}

//Combat Methods

void CompanionPriest::calculateMana()
{
	this->mana = getIntelligence() * 5.0f;
}

void CompanionPriest::increaseMana()
{
	this->mana += 10;
	std::cout << this->getName() << " prayed and recovered 10MP" << std::endl;

	if (this->mana > getIntelligence() * 5.0f)
	{
		this->setMana(getIntelligence() * 5.0f);
	}
}

void CompanionPriest::holyLight(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	this->mana -= 30;

	if (!target->dodgeAttack())
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 0.4f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageMagicDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Holy Light against " << target->getName() << " with " << damage << " points of damage" << std::endl;
			this->increaseMana();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getMagicAttackPoints() * 0.4f;
			float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageMagicDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << this->getName() << " used Holy Light against " << target->getName() << " with " << damage << " points of damage" << std::endl;
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

void CompanionPriest::heal(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, Character* target)
{
	this->mana -= 60;

	float skillDamageBonus = this->getMagicAttackPoints() * 0.8f;
	float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
	float averageHeal = calculateAverageMagicDamage(skillDamage);

	target->restoreHealth(averageHeal);
	std::cout << this->getName() << " used Heal, " << target->getName() << " got " << averageHeal << " points of health" << std::endl;
	this->increaseMana();
	std::cout << std::endl;

}

void CompanionPriest::saviourRain(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	this->mana -= 90;

	if (this->criticalHit())
	{
		float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
		float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
		float criticalDamage = skillDamage * 2.0f;
		float averageDamage = calculateAverageMagicDamage(criticalDamage);
		float damage = averageDamage;

		if (damage < 0.0f)
		{
			damage = 0.0f;
		}
		std::cout << this->getName() << "Used Saviour Rain" << std::endl;

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack())
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
				std::cout << enemies[i]->getName() << " receive " << damage << " points of damage" << std::endl;
			}
		}

		for (size_t i = 0; i < allies.size(); ++i)
		{
			allies[i]->restoreHealth(damage);
		}
		std::cout << "All allies received " << damage << " points of health" << std::endl;

		this->increaseMana();
		std::cout << std::endl;
	}
	else
	{
		float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
		float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
		float averageDamage = calculateAverageMagicDamage(skillDamage);
		float damage = averageDamage;

		if (damage < 0.0f)
		{
			damage = 0.0f;
		}

		std::cout << this->getName() << "Used Saviour Rain" << std::endl;

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack())
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
				std::cout << enemies[i]->getName() << " receive " << damage << " points of damage" << std::endl;
			}
		}

		for (size_t i = 0; i < allies.size(); ++i)
		{
			allies[i]->restoreHealth(damage);
		}
		std::cout << "All allies received " << damage << " points of health" << std::endl;

		this->increaseMana();
		std::cout << std::endl;
	}

}

//Getters

float CompanionPriest::getMana() const
{
	return mana;
}

//Setters

void CompanionPriest::setMana(float mana)
{
	this->mana = mana;
}