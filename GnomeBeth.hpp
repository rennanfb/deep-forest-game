#pragma once
#include "NpCharacter.hpp"

class GnomeBeth : public NpCharacter
{
public:


	//Constructor

	GnomeBeth(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp);

	//Creator

	static GnomeBeth* createEnemy();
	virtual Bag* createNpcBag() override;

	//Skills Sets

	void npcSkillSet(std::vector <Character*> players) override;

};
