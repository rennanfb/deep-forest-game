#include "Creature.hpp"

Creature::Creature(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky) :
	name(name),
	faction(faction),
	race(race),
	strength(strength),
	agility(agility),
	constitution(constitution),
	intelligence(intelligence),
	dexterity(dexterity),
	lucky(lucky)
{}

//Uppers

void Creature::raceBonus(std::string race) 
{
	if (this->race == "Human") 
	{
		this->strength += 3;
		this->constitution += 2;
		this->dexterity += 3;

	}
	else if (this->race == "Orc")
	{
		this->constitution += 4;
		this->strength += 4;
	}
	else if (this->race == "Elf") 
	{
		this->intelligence += 3;
		this->agility += 2;
		this->dexterity += 3;
	}
}

void Creature::upStrength(float upgrade)
{
	this->strength += upgrade;
}
void Creature::upAgility(float upgrade)
{
	this->agility += upgrade;
}
void Creature::upConstitution(float upgrade)
{
	this->constitution += upgrade;
}
void Creature::upIntelligence(float upgrade)
{
	this->intelligence += upgrade;
}
void Creature::upDexterity(float upgrade)
{
	this->dexterity += upgrade;
}
void Creature::upLucky(float upgrade)
{
	this->lucky += upgrade;
}

//Getters

std::string Creature::getName() const
{
	return name;
}
std::string Creature::getFaction() const
{
	return faction;
}
std::string Creature::getRace() const
{
	return race;
}
float Creature::getStrength() const 
{
	return strength;
}
float Creature::getAgility() const 
{
	return agility;
}
float Creature::getConstitution() const 
{
	return constitution;
}
float Creature::getIntelligence() const 
{
	return intelligence;
}
float Creature::getDexterity() const
{
	return dexterity;
}
float Creature::getLucky() const 
{
	return lucky;
}

//Setters

void Creature::setName(std::string name) 
{
	this->name = name;
}
void Creature::setFaction(std::string faction) 
{
	this->faction = faction;
}
std::string Creature::setRace() 
{
	std::cout << "Which is your race?" << std::endl;
	std::cout << "Enter (1) - Human: STR +3 | CON +2 | DEX +3" << std::endl;
	std::cout << "Enter (2) - Orc: STR +4 | CON +4" << std::endl;
	std::cout << "Enter (3) - Elf: INT+3 | AGI+2 | DEX +3" << std::endl;
	std::string raceAnswer;
	std::string raceName;

	std::cin >> raceAnswer;

	if (raceAnswer == "1") {
		raceName = "Human";
	}
	else if (raceAnswer == "2")
	{
		raceName = "Orc";
	}
	else if (raceAnswer == "3")
	{
		raceName = "Elf";
	}
	else
	{
		std::cout << "You must type a available Race Number (1, 2, 3)" << std::endl;
		setRace();
	}
	return raceName;
}
void Creature::setStrength(float strength)
{
	this->strength = strength;
}
void Creature::setAgility(float agility)
{
	this->agility = agility;
}
void Creature::setConstitution(float constitution)
{
	this->constitution = constitution;
}
void Creature::setIntelligence(float intelligence)
{
	this->intelligence = intelligence;
}
void Creature::setDexterity(float intelligence)
{
	this->dexterity = dexterity;
}
void Creature::setLucky(float lucky)
{
	this->lucky = lucky;
}

