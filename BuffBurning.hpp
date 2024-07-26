#pragma once
#include "Buff.hpp"


class BuffBurning : public Buff
{
public:
	BuffBurning(Character* player, NpCharacter* npc, int duration);

	static BuffBurning* create(Character* player, NpCharacter* npc);

	void applyEffectOnPlayer() override;
	void applyEffectOnNpc() override;
};

