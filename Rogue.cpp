#include "Rogue.hpp"

//Cosntructor

Rogue::Rogue(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int stamina) :
	Character(name, faction, race, healthPoints, attackPoints, armor, dodge, criticalChance, exp, level, nextLevelExp),
	stamina(stamina)
{}

//Creator

Rogue* Rogue::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Rogue(name, faction, race, 120, 25, 25, 20, 20, 0, 1, 100, 100);
}

//Override Methods

void Rogue::showSheet() 
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Rogue Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Rogue::showCombatLayout(NpCharacter* enemy) 
{
	std::cout << std::endl;
	std::cout << " --------- " << this->getName() << " --------- " << std::endl;
	std::cout << "HP: " << this->getHealthPoints() << " | " << "SP: " << this->getStamina();
	std::cout << std::endl;
	std::cout << " --------- " << "Skills" << " --------- " << std::endl;
	std::cout << "1 - Basic Attack" << std::endl;
	std::cout << "2 - Twin Blades (40SP)" << std::endl;
	std::cout << "3 - Deep Wound (60SP)" << std::endl;
	std::cout << "4 - Seven Sins (80SP)" << std::endl;
	std::cout << std::endl;
	std::cout << "-------- Target: " << enemy->getName() << " | HP: " << enemy->getHealthPoints() << " -------- " << std::endl;
	std::cout << "*Type the number of your next attack(1, 2, 3, 4)*" << std::endl;
	std::cout << std::endl;

	int nextMove;
	std::cin >> nextMove;
	if (nextMove == 1) 
	{
		this->basicAttack(enemy);
	}
	else if (nextMove == 2) 
	{
		this->twinBlades(enemy);
	}
	else if (nextMove == 3) 
	{
		this->deepWound(enemy);
	}
	else if (nextMove == 4)
	{
		this->sevenSins(enemy);
	}
	else {
		std::cout << std::endl;
		std::cout << "You must write the number of the skills options" << std::endl;
		this->showCombatLayout(enemy);
	}
}

void Rogue::upgradeAttributes()
{
	this->upHealthPoints(45);
	this->upAttackPoints(25);
	this->upArmor(20);
}

void Rogue::healStats()
{
	this->setHealthPoints(120 + 30 * (this->level - 1));
	this->setStamina(100);
}

void Rogue::basicAttack(NpCharacter* enemy)
{
	if (this->criticalHit() == true)
	{
		int criticalDamage = this->getAttackPoints() * 2;
		int damage = criticalDamage - enemy->damageReduction();

		std::cout << this->getName() << " attacked " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
		enemy->decreaseHealth(damage);
		this->increaseStamina();
		std::cout << std::endl;
	}
	else
	{
		int damage = this->getAttackPoints() - enemy->damageReduction();
		std::cout << this->getName() << " attacked " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
		enemy->decreaseHealth(damage);
		this->increaseStamina();
		std::cout << std::endl;
	}

}

//Combat Methods

void Rogue::increaseStamina() 
{
	if (this->stamina <= 85)
	{
		this->stamina += 15;
		std::cout << this->getName() << " breathes and regenerates 20 PS" << std::endl;
	}
}


void Rogue::twinBlades(NpCharacter* enemy)
{
	if (this->getStamina() >= 40) 
	{
		this->stamina -= 40;

		if (enemy->dodgeAttack() != true) 
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 0.3;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Twin Blades against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.3;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Twin Blades against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}

}

void Rogue::deepWound(NpCharacter* enemy)
{
	if (this->getStamina() >= 60) 
	{
		this->stamina -= 60;

		if (enemy->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Deep Wound against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 0.5;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Deep Wound against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
		}
	}
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

void Rogue::sevenSins(NpCharacter* enemy)
{
	if (this->getStamina() >= 80 ) 
	{
		this->stamina -= 80;

		if (enemy->dodgeAttack() != true) {
			if (this->criticalHit() == true)
			{
				int skillDamageBonus = this->getAttackPoints() * 1.2;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;
				int criticalDamage = skillDamage * 2;

				int damage = criticalDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Seven Sins against " << enemy->getName() << " with " << criticalDamage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
			else
			{
				int skillDamageBonus = this->getAttackPoints() * 1.2;
				int skillDamage = this->getAttackPoints() + skillDamageBonus;

				int damage = skillDamage - enemy->damageReduction();
				enemy->decreaseHealth(damage);
				std::cout << this->getName() << " used Seven Sins against " << enemy->getName() << " with " << damage << " points of damage" << std::endl;
				this->increaseStamina();
				std::cout << std::endl;
			}
		}

	}
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemy);
	}
}

//Getters

int Rogue::getStamina()
{
	return stamina;
}

//Setters

void Rogue::setStamina(int stamina)
{
	this->stamina = stamina;
}
