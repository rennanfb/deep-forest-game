#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Rogue : public Character
{
protected:
	int stamina;
public:
	//Constructor
	Rogue(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int stamina);
	
	//Creator
	static Rogue* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods
	void showSheet() override;
	void showCombatLayout(NpCharacter* enemy) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;

	//Combat Methods
	void increaseStamina();
	void twinBlades(NpCharacter* enemy);
	void deepWound(NpCharacter* enemy);
	void sevenSins(NpCharacter* enemy);

	//Getters
	int getStamina();

	//Setters
	void setStamina(int stamina);

};

