#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class CompanionPriest : public Character
{
protected:
	float mana;
public:

	//Contructor

	CompanionPriest(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float mana);

	//Creator

	static CompanionPriest* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector<NpCharacter*> enemies) override;
	void showCombatLayout(Character* ally, std::vector<NpCharacter*> enemies);
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;

	//Combat Methods

	void calculeMana();
	void increaseMana();
	void holyLight(Character* ally, std::vector<NpCharacter*> enemies, NpCharacter* target);
	void heal(Character* ally, std::vector<NpCharacter*> enemies, NpCharacter* target);
	void saviourRain(Character* ally, std::vector<NpCharacter*> enemies, NpCharacter* target);

	//Getters

	float getMana() const;

	//Setters

	void setMana(float mana);

};
