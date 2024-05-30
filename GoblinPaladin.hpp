#pragma once
#include "NpCharacter.hpp"

class GoblinPaladin : public NpCharacter
{
public:

	//Constructor

	GoblinPaladin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static GoblinPaladin* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};