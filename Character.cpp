#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Bag.hpp"
#include "Buff.hpp"
#include "DebuffBurning.hpp"
#include "FindBuffIndexByName.hpp"
#include "FindDebuffIndexByName.hpp"

//Constructor

Character::Character(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp) :
	Creature(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky),
	exp(exp),
	level(level),
	nextLevelExp(nextLevelExp),
	bag(Bag::createInitialBag())
{

}

//Combat Methods

float Character::calculateAverageDamage(float damage) const
{
	float averageDamageBonus = this->getAverageAttackBase();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 2);

	int damageUpOrDownChance = dis(gen);
	if (damageUpOrDownChance == 1)
	{
		damage -= averageDamageBonus;
	}
	else
	{
		damage += averageDamageBonus;
	}
	return damage;
}

float Character::calculateAverageMagicDamage(float damage) const
{
	float averageDamageBonus = this->getAverageMagicAttackBase();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 2);

	int damageUpOrDownChance = dis(gen);
	if (damageUpOrDownChance == 1)
	{
		damage -= averageDamageBonus;
	}
	else
	{
		damage += averageDamageBonus;
	}
	return damage;
}

std::vector<NpCharacter*> Character::filterAliveEnemies(std::vector<NpCharacter*> enemies)
{
	std::vector<NpCharacter*> aliveEnemies;
	for (auto enemy : enemies)
	{
		if (enemy->isAlive())
		{
			aliveEnemies.push_back(enemy);
		}
	}
	return aliveEnemies;
}

std::vector<Character*> Character::filterAliveAllies(std::vector<Character*> allies)
{
	std::vector<Character*> aliveAllies;
	for (auto ally : allies)
	{
		if (ally->isAlive())
		{
			aliveAllies.push_back(ally);
		}
	}
	return aliveAllies;
}


int Character::chooseEnemy(const std::vector<NpCharacter*>& enemies) 
{
	while (true) 
	{
		std::cout << "Choose your target:" << std::endl;
		for (size_t i = 0; i < enemies.size(); ++i) {
				std::cout << "Enter (" << (i + 1) << ") for " << enemies[i]->getName() << " | Faction: " << enemies[i]->getFaction() << " | HP: " << enemies[i]->getHealthPoints() << std::endl;
		}

		int choice;
		std::cout << std::endl;
		std::cin >> choice;
		std::cout << std::endl;
		std::cout << "---------------------------------------------------------------------------" << std::endl;

		if (choice > 0 && choice <= static_cast<int>(enemies.size()))
		{
				return choice - 1;
		}
		else
		{
			std::cout << "Please enter a valid number between 1 and " << enemies.size() << std::endl;
		}
	}
}

int Character::chooseAlly(const std::vector<Character*>& allies)
{
	while (true)
	{
		std::cout << "Choose your target:" << std::endl;
		for (size_t i = 0; i < allies.size(); ++i) {
			std::cout << "Enter (" << (i + 1) << ") for " << allies[i]->getName() << " | Faction: " << allies[i]->getFaction() << " | HP: " << allies[i]->getHealthPoints() << std::endl;
		}

		int choice;
		std::cin >> choice;

		if (choice > 0 && choice <= static_cast<int>(allies.size()))
		{
			return choice - 1;
		}
		else
		{
			std::cout << "Please enter a valid number between 1 and " << allies.size() << std::endl;
		}
	}
}

void Character::applyBuff(Buff* buff)
{
	for (const auto& it : buffList)
	{
		if (it->getName() == buff->getName())
		{
			it->restartDuration();
			return;
		}
	}

	this->buffList.push_back(buff);

}

void Character::removeBuff(Buff* buff)
{
	int buffIndex = FindBuffIndexByName(this->buffList, buff->getName());

	if (buffIndex != -1 && this->buffList[buffIndex]->getDuration() == 0)
	{
		this->buffList.erase(this->buffList.begin() + buffIndex);
	}
}

void Character::clearBuffs()
{
	for (auto buff : buffList)
	{
		delete buff;
	}

	buffList.clear();
}

void Character::applyDebuff(Debuff* debuff)
{
	for (const auto& it : debuffList)
	{
		if (it->getName() == debuff->getName())
		{
			it->restartDuration();
			return;
		}
	}

	this->debuffList.push_back(debuff);

}

void Character::removeDebuff(Debuff* debuff)
{
	int debuffIndex = FindDebuffIndexByName(this->debuffList, debuff->getName());

	if (debuffIndex != -1 && this->debuffList[debuffIndex]->getDuration() == 0)
	{
		this->debuffList.erase(this->debuffList.begin() + debuffIndex);
	}
}

void Character::clearDebuffs()
{
	for (auto debuff : debuffList)
	{
		delete debuff;
	}

	debuffList.clear();
}


float Character::damageReduction() const
{
	float damageReduction = this->armor / 5.0f;
	return damageReduction;
}

bool Character::dodgeAttack(NpCharacter* enemy) const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(1, 100);

	float chance = dis(gen);

	chance += enemy->getPrecision() / 2;


	if (chance < this->dodge) 
	{
		std::cout << this->getName() << " dodges the attack" << std::endl;
		return true;
	}
	else 
	{
		return false;
	}
}

bool Character::criticalHit() const
{
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance < this->criticalChance) {
		std::cout <<  " * Critical Damage * " << std::endl;
		return true;
	}
	else {
		return false;
	}
}

void Character::restoreHealth(float heal)
{
	std::cout << this->getName() << " received " << heal << " health points!" << std::endl;

	this->healthPoints += heal;
	if (this->healthPoints > this->getConstitution() * 10.0f) 
	{
		this->healthPoints = this->getConstitution() * 10.0f;
	}
	
}

void Character::decreaseHealth(float damage)
{
	this->healthPoints -= damage;
	std::cout << this->getName() << " received " << damage << " points of damage!" << std::endl;
}

bool Character::isAlive() const 
{
	if (this->healthPoints > 1.0f) {
		return true;
	}
	else
	{
		return false;
	}
}

void Character::defeatEnemy(NpCharacter* enemy)
{
	std::cout << "The " << enemy->getName() << " fall down" << std::endl;
	this->increaseExp(enemy);

	if (!enemy->bag->getBagItems().empty())
	{
		this->bag->addItem(enemy->bag->getBagItems());
	}

	std::vector<Item*> items = enemy->bag->getBagItems();

	for (const auto& item : items) {
		std::cout << this->getName() << " got " << item->getItemName() << " from " << enemy->getName() << "'s corpse" << std::endl;
	}

	delete enemy;
}

//Level Up Methods

void Character::levelUp()
{
	this->level++;
	this->upgradeAttributes();
	std::cout << std::endl;
	std::cout << "+ " << this->getName() << " Level up : " << this->getLevel() << "  +" << std::endl;
	if (this->exp > this->getNextLevelExp())
	{
		int expRest = exp -= this->getNextLevelExp();

		this->upNextLevelExp(expRest);
	}
	else
	{
		this->setExp(0);
	}
}


void Character::verifyLvl()
{
	if (this->exp >= this->nextLevelExp)
	{
		this->levelUp();
	}
}

void Character::increaseExp(NpCharacter* enemy)
{
	std::cout << this->getName() << " gained " << enemy->getExp() << " experience points" << std::endl;
	this->exp += enemy->getExp();
	this->verifyLvl();
}

//Uppers


void Character::upNextLevelExp(int restExp)
{
	this->setExp(restExp);
	this->nextLevelExp += 100;
}



//Getters

float Character::getHealthPoints() const
{
	return healthPoints;
}

float Character::getAttackPoints() const
{
	return attackPoints;
}

float Character::getAverageAttackBase() const
{
	float averageAttackBase = this->attackPoints * 0.1f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, averageAttackBase);

	float averageDamage = dis(gen);
	return averageDamage;

}

float Character::getMagicAttackPoints() const
{
	return magicAttackPoints;
}

float Character::getAverageMagicAttackBase() const
{
	float averageMagicAttackBase = this->magicAttackPoints * 0.1f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, averageMagicAttackBase);

	float averageMagicDamage = dis(gen);
	return averageMagicDamage;
}

float Character::getArmor() const
{
	return armor;
}
float Character::getPrecision() const
{
	return precision;
}
int Character::getExp() const
{
	return exp;
}
int Character::getLevel() const
{
	return level;
}
int Character::getNextLevelExp() const
{
	return nextLevelExp;
}

std::vector<Buff*> Character::getBuffList() const
{
	return buffList;
}

std::vector<Debuff*> Character::getDebuffList() const
{
	return debuffList;
}

bool Character::isBuffed()
{
	if (this->buffList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Character::isDebuffed()
{
	if (this->debuffList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Setters

void Character::setHealthPoints(float healthPoints)
{
	this->healthPoints = healthPoints;
}
void Character::setAttackPoints(float attackPoints)
{
	this->attackPoints = attackPoints;
}
void Character::setMagicAttackPoints(float magicAttackPoints)
{
	this->magicAttackPoints = magicAttackPoints;
}
void Character::setArmor(float armor)
{
	this->armor = armor;
}
void Character::setPrecision(float precision)
{
	this->precision = precision;
}

void Character::setExp(int exp) 
{
	this->exp = exp;
}
void Character::setLevel(int level) 
{
	this->level = level;
}
void Character::setNextLevelExp(int nextLevelExp) 
{
	this->nextLevelExp = nextLevelExp;
}

