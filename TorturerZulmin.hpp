#pragma once
#include "NpCharacter.hpp"

class TorturerZulmin : public NpCharacter
{
public:

	//Constructor

	TorturerZulmin(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static TorturerZulmin* createEnemy();

	//Skills Sets

	void npcSkillSet(NpCharacter* npc, Character* player) override;

};