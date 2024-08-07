#pragma once
#include "NpCharacter.hpp"

class InjuriedSeiren : public NpCharacter
{
public:

	//Constructor

	InjuriedSeiren(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexteriryt, float lucky, int exp);

	//Creator

	static InjuriedSeiren* createEnemy();
	virtual Bag* createNpcBag() override;

	//Skills Sets

	void npcSkillSet(std::vector <Character*> players) override;

};