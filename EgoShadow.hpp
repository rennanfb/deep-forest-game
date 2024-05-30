#pragma once
#include "NpCharacter.hpp"

class EgoShadow : public NpCharacter
{
public:

	//Constructor

	EgoShadow(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static EgoShadow* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};
