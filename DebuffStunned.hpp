#pragma once
#include "Debuff.hpp"

class DebuffStunned : public Debuff
{
public:
	DebuffStunned(std::string name, Creature* user, Creature* target, int duration);

	static DebuffStunned* create(Creature* user, Creature* target);

	void applyEffect() override;
	void removeEffectCheck() override;
	void restartDuration() override;
};

