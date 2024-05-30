#pragma once
#include <iostream>
#include <string>
#include <vector>

class Creature
{
private:

	//Identification

	std::string name;
	std::string faction;
	std::string race;

	//Attributes

	float strength;
	float agility;
	float constitution;
	float intelligence;
	float lucky;

public:

	//Constructor

	Creature(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky);

	//Uppers

	void raceBonus(std::string race);
	void upStrength(float upgrade);
	void upAgility(float upgrade);
	void upConstitution(float upgrade);
	void upIntelligence(float upgrade);
	void upLucky(float upgrade);

	//Getters

	std::string getName() const;
	std::string getFaction() const;
	std::string getRace() const;
	float getStrength() const;
	float getAgility() const;
	float getConstitution() const;
	float getIntelligence() const;
	float getLucky() const;

	//Setters

	void setStrength(float strength);
	void setAgility(float agility);
	void setConstitution(float constitution);
	void setIntelligence(float intelligence);
	void setLucky(float lucky);
	void setName(std::string name);
	void setFaction(std::string faction);
	static std::string setRace();
};

