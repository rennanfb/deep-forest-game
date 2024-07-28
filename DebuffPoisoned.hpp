#pragma once
#include "Debuff.hpp"

class DebuffPoisoned : public Debuff
{
public:
	DebuffPoisoned(std::string name, Creature* user, Creature* target, int duration);

	static DebuffPoisoned* create(Creature* user, Creature* target);

	void applyEffect() override;
	void removeEffectCheck() override;
	void restartDuration() override;
};

