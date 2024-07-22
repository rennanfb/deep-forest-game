#include "Hunter.hpp"

//Constructor

Hunter::Hunter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float focus) :
	Character(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp, level, nextLevelExp),
	focus(focus)
{
	calculateCombatStatus();
}

//Creator

Hunter* Hunter::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Hunter(name, faction, race, 5.0f, 13.0f, 12.0f, 8.0f, 20.0f, 13.0f, 0, 1, 100, 100.0f);
}

//Override Methods

void Hunter::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Priest Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << " | Armor Power: " << getArmor() << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << " | M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Hunter::showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
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
		std::cout << "|3| - Hunting Arrow (70MP)" << std::endl;
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

				this->doubleShot(target);
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

				this->huntingArrow(enemies, target);
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
				this->arrowStorm(aliveEnemies);
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

void Hunter::upgradeAttributes()
{
	this->upStrength(1.0f);
	this->upAgility(3.0f);
	this->upConstitution(2.0);
	this->upIntelligence(3.0);
	this->upDexterity(5.0f);
	this->upLucky(3.0);
	calculateCombatStatus();
}

void Hunter::healStats()
{

	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->calculateFocus();

}

void Hunter::basicAttack(NpCharacter* target)
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
				damage = 0;
			}

			target->decreaseHealth(damage);
			std::cout << "It caused " << criticalDamage << " points of damage!" << std::endl;
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
			std::cout << "It caused " << damage << " points of damage!" << std::endl;
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

void Hunter::restoreEnergy(float energyAmount)
{
	this->focus += energyAmount;

	if (this->focus > 100.0f + (getDexterity() / 3.0f))
	{
		this->calculateFocus();
	}
}

void Hunter::calculateCombatStatus()
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

void Hunter::calculateFocus()
{
	this->focus = 100.0f + (getDexterity() / 3.0f);
}

void Hunter::increaseFocus()
{
	this->focus += 10.0f;
	std::cout << this->getName() << " concentrates and recovered 10FP" << std::endl;

	if (this->focus > 100.0f + (getDexterity() / 3.0f))
	{
		this->calculateFocus();
	}
}

void Hunter::doubleShot(NpCharacter* target)
{
	this->focus -= 30.0f;

	std::cout << this->getName() << " used Double Shot against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 0.7f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			this->increaseFocus();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 0.7f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
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

void Hunter::huntingArrow(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	this->focus -= 60.0f;

	std::cout << this->getName() << " used Hunting Arrow against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 1.0f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, (enemies.size() - 1));

			int target2 = dis(gen);

			target->decreaseHealth(damage);
			std::cout << "The arrow pierces the target hunting another body" << std::endl;
			enemies[target2]->decreaseHealth(damage);
			this->increaseFocus();
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 1.0f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
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

void Hunter::arrowStorm(std::vector<NpCharacter*> enemies)
{
	this->focus -= 100.0f;

	std::cout << this->getName() << " used Arrow Storm " << std::endl;

	if (this->criticalHit())
	{
		float skillDamageBonus = this->getAttackPoints() * 1.3f;
		float skillDamage = this->getAttackPoints() + skillDamageBonus;
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

		this->increaseFocus();
		std::cout << std::endl;
	}
	else
	{
		float skillDamageBonus = this->getAttackPoints() * 1.3f;
		float skillDamage = this->getAttackPoints() + skillDamageBonus;
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

		this->increaseFocus();
		std::cout << std::endl;
	}

}

//Getters

float Hunter::getFocus() const
{
	return focus;
}

//Setters

void Hunter::setFocus(float mana)
{
	this->focus = mana;
}