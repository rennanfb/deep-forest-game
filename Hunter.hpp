#pragma once
#include "Character.hpp"
#include "NpCharacter.hpp"

class Hunter : public Character
{
protected:
	float focus;
public:

	//Contructor

	Hunter(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp, int level, int nextLevelExp, float focus);

	//Creator

	static Hunter* createCharacter(std::string name, std::string faction, std::string race);
	static Hunter* createQing(int level);

	//Override Methods

	void showSheet() const override;
	void showCombatLayout(std::vector<Character*> allies, std::vector<NpCharacter*> enemies) override;
	void upgradeAttributes() override;
	void checkLevelAttributes() override;
	void healStats() override;
	void basicAttack(NpCharacter* enemy) override;
	void restoreEnergy(float energyAmount) override;
	void calculateCombatStatus() override;

	//Combat Methods

	void calculateFocus();
	void increaseFocus();
	void doubleShot(NpCharacter* target);
	void huntingArrow(std::vector<NpCharacter*> enemies, NpCharacter* target);
	void arrowStorm(std::vector<NpCharacter*> enemies);

	//Getters

	float getFocus() const;

	//Setters

	void setFocus(float focus);

};
