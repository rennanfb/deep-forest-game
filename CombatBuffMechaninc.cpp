#include "CombatBuffMechaninc.hpp"

void CombatBuffMechanic(NpCharacter* enemy)
{
	std::vector<Buff*> toRemove;

	if (enemy->isBuffed())
	{
		std::vector<Buff*> toRemove;

		for (auto buff : enemy->getBuffList())
		{
			if (buff->getDuration() > 0)
			{
				buff->applyEffect();
				buff->decreaseDuration();
			}
			else if (buff->getDuration() <= 0)
			{
				buff->removeEffectCheck();
				toRemove.push_back(buff);
			}
		}

		for (auto buff : toRemove)
		{
			enemy->removeBuff(buff);
			delete buff;
		}
	}
}

void CombatBuffMechanic(Character* player)
{
	std::vector<Buff*> toRemove;

	for (auto buff : player->getBuffList())
	{
		if (buff->getDuration() > 0)
		{
			buff->applyEffect();
			buff->decreaseDuration();
		}
		else if (buff->getDuration() <= 0)
		{
			buff->removeEffectCheck();
			toRemove.push_back(buff);
		}
	}

	for (auto buff : toRemove)
	{
		player->removeBuff(buff);
		delete buff;
	}
}