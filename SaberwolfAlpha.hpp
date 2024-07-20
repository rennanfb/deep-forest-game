#pragma once
#include "NpCharacter.hpp"

class SaberwolfAlpha : public NpCharacter
{
public:

	//Constructor

	SaberwolfAlpha(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp);

	//Creator

	static SaberwolfAlpha* createEnemy();
	virtual Bag* createNpcBag() override;

	//Skills Sets

	void npcSkillSet(std::vector <Character*> players) override;

};