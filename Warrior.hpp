#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Warrior : public Character
{
protected:
	int fury;
public:
	//Constructor
	Warrior(std::string name, std::string faction, std::string race, int healthPoints, int attackPoints, int armor, int dodge, int criticalChance, int exp, int level, int nextLevelExp, int fury);
	
	//Creator
	static Warrior* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods
	void showCombatLayout(NpCharacter* enemy) override;
	void showSheet() override;
	void decreaseHealth(int damage) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;

	//Combat Methods
	void increaseFury(int damage);
	void swordShout(NpCharacter* enemy);
	void rockBreaker(NpCharacter* enemy);
	void chaosSword(NpCharacter* enemy);

	//Getters
	int getFury();

	//Setters
	void setFury(int increaseFury);

};

