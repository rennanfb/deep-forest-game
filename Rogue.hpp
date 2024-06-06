#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Rogue : public Character
{
protected:

	int stamina;

public:

	//Constructor

	Rogue(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float lucky, int exp, int level, int nextLevelExp, int stamina);
	
	//Creator

	static Rogue* createCharacter(std::string name, std::string faction, std::string race);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;

	//Combat Methods

	void increaseStamina();
	void twinBlades(std::vector<NpCharacter*> enemies, NpCharacter* target);
	void deepWound(std::vector<NpCharacter*> enemies, NpCharacter* target);
	void sevenSins(std::vector<NpCharacter*> enemies, NpCharacter* target);

	//Getters

	int getStamina() const;

	//Setters

	void setStamina(int stamina);

};

