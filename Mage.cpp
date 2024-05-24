#include "Mage.hpp"

//Constructor

Mage::Mage(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int mana) :
	Character(name, faction, race, healthPoints, attackPoints, armor, dodge, criticalChance, exp, level, nextLevelExp),
	mana(mana) 
{}

//Creator

Mage* Mage::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Mage(name, faction, race, 100, 35, 15, 8, 5, 0, 1, 100, 100);
}

//Override Methods

void Mage::showSheet() 
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Mage Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Mage::showCombatLayout(NpCharacter* enemy) 
{
	std::cout << std::endl;
	std::cout << " --------- " << this->getName() << " --------- " << std::endl;
	std::cout << "HP: " << this->getHealthPoints() << " | " << "MP: " << this->getMana();
	std::cout << std::endl;
	std::cout << " --------- " << "Skills" << " --------- " << std::endl;
	std::cout << "1 - Basic Attack" << std::endl;
	std::cout << "2 - Fire Ball (30MP)" << std::endl;
	std::cout << "3 - Earthquake (60MP)" << std::endl;
	std::cout << "4 - Cloud Strife (90MP)" << std::endl;
	std::cout << std::endl;
	std::cout << "-------- Target: " << enemy->getName() << " | HP: " << enemy->getHealthPoints() << " -------- " << std::endl;
	std::cout << "*Type the number of your next attack(1, 2, 3, 4)*" << std::endl;
	std::cout << std::endl;

	int nextMove;
	std::cin >> nextMove;
	std::cout << std::endl;
	if (nextMove == 1) 
	{
		this->basicAttack(enemy);
	}
	else if (nextMove == 2) 
	{
		this->fireBall(enemy);
	}
	else if (nextMove == 3) 
	{
		this->earthQuake(enemy);
	}
	else if (nextMove == 4) 
	{
		this->cloudStrife(enemy);
	}
	else 
	{
		std::cout << "You must write the number of the skills options" << std::endl;
		this->showCombatLayout(enemy);
	}

}

void Mage::upgradeAttributes()
{
	this->upHealthPoints(30);
	this->upAttackPoints(40);
	this->upArmor(10);
}

void Mage::healStats()
{

	this->setHealthPoints(100 + 20 * (this->level - 1));
	this->setMana(100);

}

void Mage::basicAttack(NpCharacter* enemy)
{
	if (this->criticalHit() == true) {
		int damagePenality = this->getAttackPoints() / 3;
		int criticalDamage = damagePenality * 2;
		int damage = criticalDamage - enemy->damageReduction();

		std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
		enemy->decreaseHealth(damage);
		this->increaseMana();
		std::cout << std::endl;
	}
	else
	{
		int damagePenality = this->getAttackPoints() / 3;
		int damage = damagePenality - enemy->damageReduction();
		std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
		enemy->decreaseHealth(damage);
		this->increaseMana();
		std::cout << std::endl;
	}
}

//Combat Methods

void Mage::increaseMana() 
{
	if (this->mana <= 90)
	{
		this->mana += 10;
		std::cout << this->getName() << " meditated and recovered 10MP" << std::endl;
	}
}

void Mage::fireBall(NpCharacter* enemy)
{
	if (this->getMana() >= 30) 
	{
		this->mana -= 30;

		if (enemy->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Fire Ball against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Fire Ball against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient mana, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}

}

void Mage::earthQuake(NpCharacter* enemy)
{
	if (this->getMana() >= 60)
	{
		this->mana -= 60;

		if (enemy->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 0.8;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Earthquake against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.8;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Earthquake against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient mana, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

void Mage::cloudStrife(NpCharacter* enemy)
{
	if (this->getMana() >= 90 && enemy->dodgeAttack() != true) 
	{
		this->mana -= 90;

		if (enemy->dodgeAttack() != true) 
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 1.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Cloud Strife against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 1.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Cloud Strife against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseMana();
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient mana, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

//Getters

int Mage::getMana()
{
	return mana;
}

//Setters

void Mage::setMana(int mana)
{
	this->mana = mana;
}