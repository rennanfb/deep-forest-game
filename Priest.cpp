#include "Priest.hpp"
#include "BuffBlessed.hpp"

//Constructor

Priest::Priest(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float mana) :
	Character(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp, level, nextLevelExp),
	mana(mana)
{
	calculateCombatStatus();
}

//Creator

Priest* Priest::createCharacter(std::string name, std::string faction, std::string race)
{
	return new Priest(name, faction, race, 5.0f, 5.0f, 15.0f, 18.0f, 10.0f, 5.0f, 0, 1, 100, 100.0f);
}

Priest* Priest::createLuna(int level)
{
	return new Priest("Luna", "Sundeva", "Human", 5.0f, 5.0f, 15.0f, 18.0f, 10.0f, 5.0f, 0, level, 100, 100.0f);
}

//Override Methods

void Priest::showSheet() const
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

void Priest::showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies = filterAliveEnemies(enemies);

	if (!aliveEnemies.empty())
	{
		std::cout << "- " << this->getName() << "'s turn -" << std::endl;

		std::cout << std::endl;
		std::cout << " --------- " << this->getName() << " --------- " << std::endl;
		std::cout << "HP: " << this->getHealthPoints() << " | " << "MP: " << this->getMana();
		std::cout << std::endl;
		std::cout << "Str: " << this->getStrength() << " | Agi: " << this->getAgility() << " | Con: " << this->getConstitution() << " | Int: " << this->getIntelligence() << " | Dex: " << this->getDexterity() << " | Luk: " << this->getLucky() << std::endl;
		std::cout << " --------- " << "Skills" << " --------- " << std::endl;
		std::cout << "|1| - Basic Attack" << std::endl;
		std::cout << "|2| - Heal (30MP) - Heal an ally" << std::endl;
		std::cout << "|3| - Holy Light (60MP) - Bless all allies with strength, constitution and Lucky upgrades" << std::endl;
		std::cout << "|4| - Saviour Rain (90MP) - A holy rain that cause damage to enemies and heal the allies" << std::endl;
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
			if (this->getMana() >= 29.5f)
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
		else if (nextMove == 3)
		{
			if (this->getMana() >= 59.5f)
			{
				std::vector<Character*> aliveAllies = filterAliveAllies(allies);
				this->holyLight(aliveAllies);
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

void Priest::upgradeAttributes()
{
	this->upStrength(1.0f);
	this->upAgility(2.0f);
	this->upConstitution(3.0f);
	this->upIntelligence(4.0f);
	this->upDexterity(2.0f);
	this->upLucky(3.0f);
	calculateCombatStatus();
}

void Priest::checkLevelAttributes()
{
	for (size_t i = 0; i < this->getLevel(); ++i)
	{
		this->upStrength(1.0f);
		this->upAgility(2.0f);
		this->upConstitution(3.0f);
		this->upIntelligence(4.0f);
		this->upDexterity(2.0f);
		this->upLucky(3.0f);
		this->nextLevelExp += 100;
	}
	calculateCombatStatus();
}

void Priest::healStats()
{

	this->setHealthPoints(this->getConstitution() * 10.0f);
	this->calculateMana();

}

void Priest::basicAttack(NpCharacter* target)
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

void Priest::restoreEnergy(float energyAmount)
{
	this->mana += energyAmount;

	if (this->mana > 100.0f + (getIntelligence() / 3.0f))
	{
		this->calculateMana();
	}
}

void Priest::decreaseEnergy(float energyAmount)
{
	this->mana -= energyAmount;

	if (this->mana < 0.0f)
	{
		this->mana = 0.0f;
	}
}

void Priest::calculateCombatStatus()
{
	this->healthPoints = this->getConstitution() * 7.0f;
	this->attackPoints = this->getStrength() * 1.5f;
	this->magicAttackPoints = this->getIntelligence() * 1.8f;
	this->armor = this->getConstitution() * 1.5f;
	this->dodge = this->getAgility() / 2.0f;
	this->precision = this->getDexterity() / 2.0f;
	this->criticalChance = this->getLucky() / 2.0f;
}

//Combat Methods

void Priest::calculateMana()
{
	this->mana = 100.0f + (getIntelligence() / 3.0f);
}

void Priest::increaseMana()
{
	this->mana += 10.0f;
	std::cout << this->getName() << " prayed and recovered 10MP" << std::endl;

	if (this->mana > 100.0f + (getIntelligence() / 3.0f))
	{
		calculateMana();
	}
}

void Priest::heal(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, Character* target)
{
	this->mana -= 30.0f;

	std::cout << this->getName() << " healed " << target->getName() << std::endl;

	float skillDamageBonus = this->getMagicAttackPoints() * 0.5f;
	float skillDamage = this->getMagicAttackPoints() + skillDamageBonus;
	float averageHeal = calculateAverageMagicDamage(skillDamage);

	target->restoreHealth(averageHeal);
	this->increaseMana();
	std::cout << std::endl;

}

void Priest::holyLight(std::vector<Character*> allies)
{
	this->mana -= 60.0f;

	std::cout << "All allies had been blessed by the Holy Light" << std::endl;

	for (auto ally : allies)
	{
		Buff* bless = BuffBlessed::create(this, ally);
		ally->applyBuff(bless);
	}

}

void Priest::saviourRain(std::vector<Character*> allies, std::vector<NpCharacter*> enemies)
{
	this->mana -= 90.0f;

	std::cout << this->getName() << " used Saviour Rain" << std::endl;

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

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack(this))
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
			}
		}

		for (size_t i = 0; i < allies.size(); ++i)
		{
			allies[i]->restoreHealth(damage);
		}

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


		for (size_t i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->dodgeAttack(this))
			{
				enemies[i]->decreaseHealth(damage - enemies[i]->damageReduction());
			}
		}

		for (size_t i = 0; i < allies.size(); ++i)
		{
			allies[i]->restoreHealth(damage);
		}

		this->increaseMana();
		std::cout << std::endl;
	}

}

//Getters

float Priest::getMana() const
{
	return mana;
}

//Setters

void Priest::setMana(float mana)
{
	this->mana = mana;
}