#pragma once
#include <vector>
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

class Buff
{
protected:

	std::string name;
	Creature* user;
	Creature* target;
	int duration;

public:

	Buff(std::string name, Creature* user, Creature* target, int duration);
	virtual void applyEffect() = 0;
	virtual void removeEffectCheck() = 0;
	virtual void restartDuration() = 0;

	void decreaseDuration();

	std::string getName();
	int getDuration();
};

