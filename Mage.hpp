#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Mage : public Character
{
protected:
	int mana;
public:
	//Contructor
	Mage(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int mana);

	//Creator
	static Mage* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods
	void showSheet() override;
	void showCombatLayout(NpCharacter* enemy) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;

	//Combat Methods
	void increaseMana();
	void fireBall(NpCharacter* enemy);
	void earthQuake(NpCharacter* enemy);
	void cloudStrife(NpCharacter* enemy);

	//Getters
	int getMana();

	//Setters
	void setMana(int mana);

};

