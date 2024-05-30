#include "Rogue.hpp"

//Cosntructor

Rogue::Rogue(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, int stamina) :
	Character(name, faction, race, strength, agility, constitution, intelligence, lucky, exp, level, nextLevelExp),
	stamina(stamina)
{
	calculateCombatStatus();
}

//Creator

Rogue* Rogue::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Rogue(name, faction, race, 14.0f, 16.0f, 14.0f, 5.0f, 16.0f, 0, 1, 100, 100);
}

//Override Methods

void Rogue::showSheet() const
{
	std::cout << std::endl;
	std::cout << this->getName() << " | Rogue Lv: " << this->getLevel() << " | " << this->getRace() << " | " << this->getFaction() << std::endl;
	std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Luk: " << this->getLucky() << std::endl;
	std::cout << "---- Combat Attributes ---- " << std::endl;
	std::cout << "P-Attack Power: " << getAttackPoints() << std::endl;
	std::cout << "M-Attack Power: " << getMagicAttackPoints() << std::endl;
	std::cout << "Health Points: " << getHealthPoints() << std::endl;
	std::cout << "Armor Power: " << getArmor() << std::endl;
	std::cout << "EXP: " << this->getExp() << " / " << this->getNextLevelExp() << std::endl;
	std::cout << std::endl;
}

void Rogue::showCombatLayout(std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (aliveEnemies.empty())
	{
		return;
	}

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

	int targetIndex = chooseEnemy(aliveEnemies);
	NpCharacter* target = aliveEnemies[targetIndex];

	std::cout << "*Type the number of your next attack (1, 2, 3, 4)*" << std::endl;
	int nextMove;
	std::cin >> nextMove;
	std::cout << std::endl;

	if (nextMove == 1) {
		this->basicAttack(target);
	}
	else if (nextMove == 2) {
		this->twinBlades(aliveEnemies, target);
	}
	else if (nextMove == 3) {
		this->deepWound(aliveEnemies, target);
	}
	else if (nextMove == 4) {
		this->sevenSins(aliveEnemies, target);
	}
	else {
		std::cout << "You must write the number of the skill options" << std::endl;
		this->showCombatLayout(enemies);

	}
}

void Rogue::upgradeAttributes()
{
	this->upStrength(4.0f);
	this->upAgility(5.0f);
	this->upConstitution(3.0);
	this->upIntelligence(2.0);
	this->upLucky(5.0);
	calculateCombatStatus();
}

void Rogue::healStats()
{
	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->setStamina(100);
}

void Rogue::basicAttack(NpCharacter* target)
{
	if (target->dodgeAttack() != true)
	{
		if (this->criticalHit() == true)
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
			std::cout << this->getName() << " attacked " << target->getName() << " with " << damage << " points of damage" << std::endl;
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

//Combat Methods

void Rogue::increaseStamina() 
{
	this->stamina += 15;
	std::cout << this->getName() << " breathes and regenerates 20 PS" << std::endl;

	if (this->stamina > 100) {
		this->setStamina(100);
	}
}


void Rogue::twinBlades(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getStamina() >= 40) 
	{
		this->stamina -= 40;

		if (target->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
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
				std::cout << this->getName() << " used Twin Blades against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Twin Blades against " << target->getName() << " with " << damage << " points of damage" << std::endl;
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
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemies);
	}

}

void Rogue::deepWound(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getStamina() >= 60) 
	{
		this->stamina -= 60;

		if (target->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
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
				std::cout << this->getName() << " used Deep Wound against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Deep Wound against " << target->getName() << " with " << damage << " points of damage" << std::endl;
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
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemies);
	}
}

void Rogue::sevenSins(std::vector<NpCharacter*> enemies, NpCharacter* target)
{
	if (this->getStamina() >= 80 ) 
	{
		this->stamina -= 80;

		if (target->dodgeAttack() != true)
		{
			if (this->criticalHit() == true)
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
				std::cout << this->getName() << " used Seven Sins against " << target->getName() << " with " << criticalDamage << " points of damage" << std::endl;
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
				std::cout << this->getName() << " used Seven Sins against " << target->getName() << " with " << damage << " points of damage" << std::endl;
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
	else 
	{
		std::cout << "Insufficient stamina, use another skill" << std::endl;
		this->showCombatLayout(enemies);
	}
}

//Getters

int Rogue::getStamina() const
{
	return stamina;
}

//Setters

void Rogue::setStamina(int stamina)
{
	this->stamina = stamina;
}
