#include "CombatDebuffMechanic.hpp"

void CombatDebuffMechanic(NpCharacter* enemy)
{
	std::vector<Debuff*> toRemove;

	for (auto debuff : enemy->getDebuffList())
	{
		if (debuff->getDuration() > 0)
		{
			debuff->applyEffect();
			debuff->decreaseDuration();
		}
		else if (debuff->getDuration() <= 0)
		{
			debuff->removeEffectCheck();
			toRemove.push_back(debuff);
		}
	}

	for (auto debuff : toRemove)
	{
		enemy->removeDebuff(debuff);
		delete debuff;
	}
}

void CombatDebuffMechanic(Character* player)
{
	std::vector<Debuff*> toRemove;

	if (player->isDebuffed())
	{
		std::vector<Debuff*> toRemove;

		for (auto debuff : player->getDebuffList())
		{
			if (debuff->getDuration() > 0)
			{
				debuff->applyEffect();
				debuff->decreaseDuration();
			}
			else if (debuff->getDuration() <= 0)
			{
				debuff->removeEffectCheck();
				toRemove.push_back(debuff);
			}
		}

		for (auto debuff : toRemove)
		{
			player->removeDebuff(debuff);
			delete debuff;
		}
	}
}