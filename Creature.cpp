#include "Creature.hpp"

Creature::Creature(std::string name, std::string faction, std::string race):
	name(name),
	faction(faction),
	race(race)
{}

std::string Creature::getName() 
{
	return name;
}
std::string Creature::getFaction() 
{
	return faction;
}
std::string Creature::getRace() 
{
	return race;
}

void Creature::setName(std::string name) 
{
	this->name = name;
}
void Creature::setFaction(std::string faction) 
{
	this->faction = faction;
}
void Creature::setRace(std::string race) 
{
	this->race = race;
}

