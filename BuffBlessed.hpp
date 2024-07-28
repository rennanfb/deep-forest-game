#pragma once
#include "Buff.hpp"

class BuffBlessed : public Buff
{
protected:
	bool buffApplied = false;

	float originalStrength = 0.0f;
	float originalConstitution = 0.0f;
	float originalLucky = 0.0f;

public:
	BuffBlessed(std::string name, Creature* user, Creature* target, int duration);

	static BuffBlessed* create(Creature* user, Creature* target);

	void applyEffect() override;
	void removeEffectCheck() override;
	void restartDuration() override;
};

