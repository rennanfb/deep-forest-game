#pragma once
#include "NpCharacter.hpp"

class GoblinWarrior : public NpCharacter
{
public:

	//Constructor

	GoblinWarrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static GoblinWarrior* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};