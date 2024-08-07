#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Bag.hpp"

class Mage : public Character
{
protected:

	float mana;

public:

	//Contructor

	Mage(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float mana);

	//Creator

	static Mage* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector <Character*> allies, std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void checkLevelAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;
	void decreaseEnergy(float energyAmount) override;
	void calculateCombatStatus() override;

	//Combat Methods

	void calculateMana();
	void increaseMana();
	void fireBall(NpCharacter* enemy);
	void earthQuake(std::vector<NpCharacter*> enemies);
	void cloudStrife(NpCharacter* enemy);

	//Getters

	float getMana() const;

	//Setters

	void setMana(float mana);

};

