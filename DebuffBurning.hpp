#pragma once
#include "Debuff.hpp"

class DebuffBurning : public Debuff
{
public:
	DebuffBurning(std::string name, Creature* user, Creature* target, int duration);

	static DebuffBurning* create(Creature* user, Creature* target);

	void applyEffect() override;
	void removeEffectCheck() override;
	void restartDuration() override;
};

