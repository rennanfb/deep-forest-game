#pragma once
#include "Debuff.hpp"

class DebuffBleeding : public Debuff
{
public:
	DebuffBleeding(std::string name, Creature* user, Creature* target, int duration);

	static DebuffBleeding* create(Creature* user, Creature* target);

	void applyEffect() override;
	void removeEffectCheck() override;
	void restartDuration() override;
};

