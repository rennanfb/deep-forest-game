#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Mage : public Character
{
protected:
	float mana;
public:
	//Contructor
	Mage(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, float mana);

	//Creator
	static Mage* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods
	void showSheet() const override;
	void showCombatLayout(std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;

	//Combat Methods
	void calculeMana();
	void increaseMana();
	void fireBall(std::vector<NpCharacter*> enemies, NpCharacter* enemy);
	void earthQuake(std::vector<NpCharacter*> enemies, NpCharacter* enemy);
	void cloudStrife(std::vector<NpCharacter*> enemies, NpCharacter* enemy);

	//Getters
	float getMana() const;

	//Setters
	void setMana(float mana);

};

