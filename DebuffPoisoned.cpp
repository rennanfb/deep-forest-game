#include "DebuffPoisoned.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

DebuffPoisoned::DebuffPoisoned(std::string name, Creature* user, Creature* target, int duration) :
	Debuff(name, user, target, duration)
{

}

DebuffPoisoned* DebuffPoisoned::create(Creature* user, Creature* target)
{
	return new DebuffPoisoned("Poisoned", user, target, 5);
}

void DebuffPoisoned::applyEffect()
{
	if (this->duration > 0)
	{
		float damage = target->getConstitution() / 2;

		std::cout << "* " << target->getName() << " is poisoned *" << std::endl;

		target->decreaseHealth(damage);
	}
}

void DebuffPoisoned::removeEffectCheck()
{
	return;
}

void DebuffPoisoned::restartDuration()
{
	this->duration = 5;
}



