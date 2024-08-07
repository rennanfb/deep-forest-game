#pragma once
#include <vector>
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Bag.hpp"

class Warrior : public Character
{
protected:

	float fury;

public:

	//Constructor

	Warrior(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float fury);
	
	//Creator

	static Warrior* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showCombatLayout(std::vector <Character*> allies, std::vector<NpCharacter*> enemies) override;
	void showSheet() const override;
	void decreaseHealth(float damage) override;
	void upgradeAttributes() override;
	void checkLevelAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;
	void decreaseEnergy(float energyAmount) override;
	void calculateCombatStatus() override;

	//Combat Methods

	void increaseFury(float damage);
	void swordWhirl(std::vector<NpCharacter*> enemies);
	void rockBreaker(NpCharacter* target);
	void chaosSword(NpCharacter* target);

	//Getters

	float getFury() const;

	//Setters

	void setFury(float increaseFury);

};

