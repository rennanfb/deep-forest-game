#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class CompanionPriest : public Character
{
protected:
	float mana;
public:

	//Contructor

	CompanionPriest(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence,float dexterity, float lucky, int exp, int level, int nextLevelExp, float mana);

	//Creator

	static CompanionPriest* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;
	void calculateCombatStatus() override;

	//Combat Methods

	void calculateMana();
	void increaseMana();
	void holyLight(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, NpCharacter* target);
	void heal(std::vector<Character*> allies, std::vector<NpCharacter*> enemies, Character* target);
	void saviourRain(std::vector<Character*> allies, std::vector<NpCharacter*> enemies);

	//Getters

	float getMana() const;

	//Setters

	void setMana(float mana);

};
