#pragma once
#include "NpCharacter.hpp"

class GoblinPaladin : public NpCharacter
{
public:

	//Constructor

	GoblinPaladin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp);

	//Creator

	static GoblinPaladin* createEnemy();
	virtual Bag* createNpcBag() override;

	//Skills Sets

	void npcSkillSet(std::vector <Character*> players) override;

};