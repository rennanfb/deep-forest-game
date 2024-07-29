#include "Warrior.hpp"
#include "DebuffStunned.hpp"

//Constructor

Warrior::Warrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float fury) :
	Character(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp, level, nextLevelExp),
	fury(fury)
{
	calculateCombatStatus();
}

//Creator

Warrior* Warrior::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Warrior(name, faction, race, 12.0f, 10.0f, 18.0f, 3.0f, 8.0f, 10.0f, 0, 1, 100, 0);
}

//Override Methods

void Warrior::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Warrior Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << " | Armor Power: " << getArmor() << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << " | M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Warrior::showCombatLayout(std::vector <Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{

		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "FP: " << this->getFury();
		std::cout << std::endl;
		std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
		std::cout << " ------------ " << "Skills" << " ------------ " << std::endl;
		std::cout << "|1| - Basic Attack" << std::endl;
		std::cout << "|2| - Sword Whirl (15FP) - A whirl engage that deals area damage" << std::endl;
		std::cout << "|3| - Rock Breaker (30FP) - Strong attack that stuns the target" << std::endl;
		std::cout << "|4| - Chaos Sword (60FP) - Powerful strike that ignore the target armor" << std::endl;
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
			if (this->getFury() >= 24.5f)
			{

				this->swordWhirl(enemies);
			}
			else
			{
				std::cout << "Insufficient Fury, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 3)
		{
			if (this->getFury() >= 49.5f)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->rockBreaker(target);
			}
			else
			{
				std::cout << "Insufficient Fury, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else if (nextMove == 4)
		{
			if (this->getFury() >= 79.5)
			{
				int targetIndex = chooseEnemy(aliveEnemies);
				NpCharacter* target = aliveEnemies[targetIndex];

				this->chaosSword(target);
			}
			else
			{
				std::cout << "Insufficient Fury, select a possible move" << std::endl;
				this->showCombatLayout(allies, enemies);
			}
		}
		else {
			std::cout << "You must write the number of the skill options" << std::endl;
			this->showCombatLayout(allies, enemies);

		}
	}
	else
	{
		return;
	}
}


void Warrior::decreaseHealth(float damage)
{
	this->healthPoints -= damage;
	std::cout << this->getName() << " received " << damage << " points of damage!" << std::endl;
	increaseFury(damage);
}

void Warrior::upgradeAttributes()
{
	this->upStrength(5.0f);
	this->upAgility(2.0f);
	this->upConstitution(5.0f);
	this->upIntelligence(2.0f);
	this->upDexterity(1.0f);
	this->upLucky(3.0f);
	calculateCombatStatus();
}

void Warrior::checkLevelAttributes()
{
	for (size_t i = 0; i < this->getLevel(); ++i)
	{
		this->upStrength(5.0f);
		this->upAgility(2.0f);
		this->upConstitution(5.0f);
		this->upIntelligence(2.0f);
		this->upDexterity(1.0f);
		this->upLucky(3.0f);
		this->nextLevelExp += 100;
	}
	calculateCombatStatus();
}

void Warrior::healStats()
{
	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setFury(0.0f);
}

void Warrior::basicAttack(NpCharacter* target)
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
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

void Warrior::restoreEnergy(float energyAmount) 
{
	this->fury += energyAmount;

	if (this->fury > 100.0f)
	{
		this->setFury(100.0f);
	}
}

void Warrior::calculateCombatStatus()
{
	this->healthPoints = this->getConstitution() * 11.0f;
	this->attackPoints = this->getStrength() * 1.5f;
	this->magicAttackPoints = this->getIntelligence() * 1.5f;
	this->armor = this->getConstitution() * 3.5f;
	this->dodge = this->getAgility() / 2.5f;
	this->precision = this->getDexterity() / 2.5f;
	this->criticalChance = this->getLucky() / 1.5f;
}

//Combat Methods

void Warrior::increaseFury(float damageTaken) 
{
	if (this->fury < 100.0)
	{
		float furyBoost = 10.0f + (damageTaken / 2.0f);
		this->fury += furyBoost;
		std::cout << "Warrior gets " << furyBoost << " points of fury" << std::endl;
		if (this->fury > 100.0f) 
		{
			this->setFury(100.0f);
		}
	}
}

void Warrior::swordWhirl(std::vector<NpCharacter*> enemies)
{
	this->fury -= 25.0f;

	std::cout << this->getName() << " used Sword Whirl" << std::endl;


	if (this->criticalHit())
	{
		float skillDamageBonus = this->getAttackPoints() * 0.7f;
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
		std::cout << std::endl;
	}
	else
	{
		float skillDamageBonus = this->getAttackPoints() * 0.7f;
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
		std::cout << std::endl;
	}

}

void Warrior::rockBreaker(NpCharacter* target)
{
	this->fury -= 50.0f;

	std::cout << this->getName() << " used Rock Breaker against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit()) 
		{
			float skillDamageBonus = this->getAttackPoints() * 0.8f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 0.8f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage - target->damageReduction();

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << std::endl;
		}

		Debuff* stun = DebuffStunned::create(this, target);
		target->applyDebuff(stun);
	}
	else
	{
	return;
	}
}

void Warrior::chaosSword(NpCharacter* target)
{
	this->fury -= 80.0f;

	std::cout << this->getName() << " used Chaos Sword against " << target->getName() << std::endl;

	if (!target->dodgeAttack(this))
	{
		if (this->criticalHit())
		{
			float skillDamageBonus = this->getAttackPoints() * 1.2f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float criticalDamage = skillDamage * 2.0f;
			float averageDamage = calculateAverageDamage(criticalDamage);
			float damage = averageDamage;

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << std::endl;
		}
		else
		{
			float skillDamageBonus = this->getAttackPoints() * 1.2f;
			float skillDamage = this->getAttackPoints() + skillDamageBonus;
			float averageDamage = calculateAverageDamage(skillDamage);
			float damage = averageDamage;

			if (damage < 0.0f)
			{
				damage = 0.0f;
			}

			target->decreaseHealth(damage);
			std::cout << std::endl;
		}
	}
	else
	{
		return;
	}
}

//Getters

float Warrior::getFury() const
{
	return fury;
}

//Setters

void Warrior::setFury(float fury)
{
	this->fury = fury;
}