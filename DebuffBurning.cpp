#include "DebuffBurning.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

DebuffBurning::DebuffBurning(std::string name, Creature* user, Creature* target, int duration) :
	Debuff(name, user, target, duration)
{

}

DebuffBurning* DebuffBurning::create(Creature* user, Creature* target)
{
	return new DebuffBurning("Burning", user, target, 2);
}

void DebuffBurning::applyEffect()
{
	if (this->duration > 0)
	{
		float damage = user->getIntelligence();

		damage -= target->damageReduction();

		if (damage < 5.0f)
		{
			damage = 5.0f;
		}

		std::cout << "* " << target->getName() << " is burning *" << std::endl;

		target->decreaseHealth(damage);
	}
}

void DebuffBurning::removeEffectCheck()
{
	return;
}

void DebuffBurning::restartDuration()
{
	this->duration = 2;
}



