#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Bag.hpp"

class Rogue : public Character
{
protected:

	float stamina;

public:

	//Constructor

	Rogue(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float stamina);
	
	//Creator

	static Rogue* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;

	//Combat Methods

	void increaseStamina();
	void twinBlades(std::vector<NpCharacter*> enemies, NpCharacter* target);
	void deepWound(std::vector<NpCharacter*> enemies, NpCharacter* target);
	void sevenSins(std::vector<NpCharacter*> enemies, NpCharacter* target);

	//Getters

	float getStamina() const;

	//Setters

	void setStamina(float stamina);

};

