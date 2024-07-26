#include "BuffBurning.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

BuffBurning::BuffBurning(Character* player, NpCharacter* npc, int duration) :
	Buff(player, npc, duration)
{

}

BuffBurning* BuffBurning::create(Character* player, NpCharacter* npc)
{
	return new BuffBurning(player, npc, 2);
}


void BuffBurning::applyEffectOnNpc() 
{
	if (this->duration > 0)
	{
		float damage = player->getIntelligence();

		damage -= npc->damageReduction();

		if (damage < 5.0f)
		{
			damage = 5.0f;
		}

		std::cout << "* " << npc->getName() << "is burning *" << std::endl;

		npc->decreaseHealth(damage);
	}
	else
	{
		delete this;
	}
}

void BuffBurning::applyEffectOnPlayer()
{
	if (this->duration > 0)
	{
		float damage = npc->getIntelligence();

		damage -= player->damageReduction();

		if (damage < 5.0f)
		{
			damage = 5.0f;
		}

		std::cout << "* " << player->getName() << "is burning *" << std::endl;
		player->decreaseHealth(damage);
	}
	else
	{
		delete this;
	}
}


