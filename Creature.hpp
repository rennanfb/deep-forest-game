#pragma once
#include <string>

class Creature
{
private:
	std::string name;
	std::string faction;
	std::string race;

public:
	//Constructor
	Creature(std::string name, std::string faction, std::string race);

	//Getters
	std::string getName();
	std::string getFaction();
	std::string getRace();

	//Setters
	void setName(std::string name);
	void setFaction(std::string faction);
	void setRace(std::string race);
};

