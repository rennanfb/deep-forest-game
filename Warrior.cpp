#include "Warrior.hpp"

//Constructor

Warrior::Warrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float fury) :
	Character(name, faction, race, strength, agility, constitution, intelligence, lucky, exp, level, nextLevelExp),
	fury(fury)
{
	calculateCombatStatus();
}

//Creator

Warrior* Warrior::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Warrior(name, faction, race, 12.0f, 10.0f, 18.0f, 3.0f, 10.0f, 0, 1, 100, 0);
}

//Override Methods

void Warrior::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Warrior Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Warrior::showCombatLayout(std::vector<NpCharacter*> enemies)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (aliveEnemies.empty())
	{
		return;
	}

	int targetIndex = chooseEnemy(aliveEnemies);
	NpCharacter* target = aliveEnemies[targetIndex];


	std::cout << std::endl;
	std::cout << " --------- " << this->getName() << " --------- " << std::endl;
	std::cout << "HP: " << this->getHealthPoints() << " | " << "FP: " << this->getFury();
	std::cout << std::endl;
	std::cout << " --------- " << "Skills" << " --------- " << std::endl;
	std::cout << "1 - Basic Attack" << std::endl;
	std::cout << "2 - Sword Shout (15FP)" << std::endl;
	std::cout << "3 - Rock Breaker (30FP)" << std::endl;
	std::cout << "4 - Chaos Sword (60FP)" << std::endl;
	std::cout << std::endl;

	std::cout << "* Enter the number of your next attack (1, 2, 3, 4) or Enter (0) to access your bag *" << std::endl;
	int nextMove;
	std::cin >> nextMove;
	std::cout << std::endl;

	
	if (nextMove == 0) 
	{
		this->bag->showBagLayout(enemies, this);
	}
	else if (nextMove == 1) 
	{
		this->basicAttack(target);
	}
	else if (nextMove == 2) 
	{
		this->swordShout(aliveEnemies, target);
	}
	else if (nextMove == 3) 
	{
		this->rockBreaker(aliveEnemies, target);
	}
	else if (nextMove == 4) 
	{
		this->chaosSword(aliveEnemies, target);
	}
	else {
		std::cout << "You must write the number of the skill options" << std::endl;
		this->showCombatLayout(enemies);

	}
}


void Warrior::decreaseHealth(float damage)
{
	this->healthPoints -= damage;
	increaseFury(damage);
}

void Warrior::upgradeAttributes()
{
	this->upStrength(5.0f);
	this->upAgility(2.0f);
	this->upConstitution(5.0);
	this->upIntelligence(2.0);
	this->upLucky(3.0);
	calculateCombatStatus();
}

void Warrior::healStats()
{
	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setFury(0.0f);
}

void Warrior::basicAttack(NpCharacter* target)
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

//Combat Methods

void Warrior::increaseFury(float damageTaken) 
{
	if (this->fury < 100.0)
	{
		float furyBoost = damageTaken / 2.0f;
		this->fury += furyBoost;
		std::cout << "Warrior gets " << furyBoost << " points of fury" << std::endl;
		if (this->fury > 100.0f) 
		{
			this->setFury(100.0f);
		}
	}
}

void Warrior::swordShout(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getFury() >= 15.0f )
	{
		this->fury -= 15.0f;

		if (!target->dodgeAttack())
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
				std::cout << this->getName() << " used Sword Shout against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Sword Shout against " << target->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
		else
		{
			return;
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemies);
	}

}

void Warrior::rockBreaker(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getFury() >= 30.0f) 
	{
		this->fury -= 30.0f;

		if (!target->dodgeAttack())
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
				std::cout << this->getName() << " used Rock Breaker against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Rock Breaker against " << target->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
		else
		{
			return;
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemies);
	}
}

void Warrior::chaosSword(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getFury() >= 60.0f ) 
	{
		this->fury -= 60.0f;

		if (!target->dodgeAttack())
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
				std::cout << this->getName() << " used Chaos Sword against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Chaos Sword against " << target->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
		else
		{
			return;
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemies);
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