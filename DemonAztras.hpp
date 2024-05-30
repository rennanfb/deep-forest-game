#pragma once
#include "NpCharacter.hpp"

class DemonAztras : public NpCharacter
{
public:

	//Constructor

	DemonAztras(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static DemonAztras* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};
