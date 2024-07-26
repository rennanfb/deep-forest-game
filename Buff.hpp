#pragma once
#include <vector>
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

class Buff
{
protected:

	Character* player;
	NpCharacter* npc;
	int duration;

public:

	Buff(Character* player, NpCharacter* npc, int duration);
	virtual void applyEffectOnPlayer() = 0;
	virtual void applyEffectOnNpc() = 0;

	void decreaseDuration();
};

