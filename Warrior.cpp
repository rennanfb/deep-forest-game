#include "Warrior.hpp"

//Constructor

Warrior::Warrior(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int fury) :
	Character(name, faction, race, healthPoints, attackPoints, armor, dodge, criticalChance, exp, level, nextLevelExp),
	fury(fury) {}

//Creator

Warrior* Warrior::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Warrior(name, faction, race, 150, 20, 40, 5, 10, 0, 1, 100, 0);
}

//Override Methods

void Warrior::showSheet() 
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Warrior Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Warrior::showCombatLayout(NpCharacter* enemy) 
{
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
	std::cout << "-------- Target: " << enemy->getName() << " | HP: " << enemy->getHealthPoints() << " -------- " << std::endl;
	std::cout << "*Type the number of your next attack(1, 2, 3, 4)*" << std::endl;
	std::cout << std::endl;

	int nextMove;
	std::cin >> nextMove;
	if (nextMove == 1) {
		this->basicAttack(enemy);
	}
	else if (nextMove == 2) 
	{
		this->swordShout(enemy);
	}
	else if (nextMove == 3) 
	{
		this->rockBreaker(enemy);
	}
	else if (nextMove == 4) 
	{
		this->chaosSword(enemy);
	}
	else {
		std::cout << std::endl;
		std::cout << "You must write the number of the skills options" << std::endl;
		this->showCombatLayout(enemy);
	}
}


void Warrior::decreaseHealth(int damage)
{
	this->healthPoints -= damage;
	increaseFury(damage);
}

void Warrior::upgradeAttributes()
{
	this->upHealthPoints(65);
	this->upAttackPoints(15);
	this->upArmor(30);
}

void Warrior::healStats()
{
	this->setHealthPoints(150 + 40 * (this->level - 1));
	this->setFury(0);
}

void Warrior::basicAttack(NpCharacter* enemy)
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

//Combat Methods

void Warrior::increaseFury(int damageTaken) 
{
	if (this->fury < 100)
	{
		int furyBoost = damageTaken / 2;
		this->fury += furyBoost;
		std::cout << "Warrior gets " << furyBoost << " points of fury" << std::endl;
		if (this->fury > 100) 
		{
			this->setFury(100);
		}
	}
}

void Warrior::swordShout(NpCharacter* enemy) 
{
	if (this->getFury() >= 15 )
	{
		this->fury -= 15;

		if (enemy->dodgeAttack() != true) 
		{

			if (this->criticalHit() == true) 
			{

				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Sword Shout against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Sword Shout against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}

}

void Warrior::rockBreaker(NpCharacter* enemy)
{
	if (this->getFury() >= 30) 
	{
		this->fury -= 30;

		if (enemy->dodgeAttack() != true) 
		{
			if (this->criticalHit() == true) 
			{
				int skillDamageBonus = this->getAttackPoints() * 0.8;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Rock Breaker against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.8;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Rock Breaker against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

void Warrior::chaosSword(NpCharacter* enemy)
{
	if (this->getFury() >= 60 ) 
	{
		this->fury -= 60;

		if (enemy->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 1.2;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Chaos Sword against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 1.2;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Chaos Sword against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient fury, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

//Getters

int Warrior::getFury()
{
	return fury;
}

//Setters

void Warrior::setFury(int fury)
{
	this->fury = fury;
}