#pragma once
#include "NpCharacter.hpp"

class GnomeRath : public NpCharacter
{
public:

	//Constructor

	GnomeRath(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static GnomeRath* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};
