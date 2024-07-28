#include "DebuffBleeding.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

DebuffBleeding::DebuffBleeding(std::string name, Creature* user, Creature* target, int duration) :
	Debuff(name, user, target, duration)
{

}

DebuffBleeding* DebuffBleeding::create(Creature* user, Creature* target)
{
	return new DebuffBleeding("Bleeding", user, target, 4);
}

void DebuffBleeding::applyEffect()
{
	if (this->duration > 0)
	{
		float damage = user->getDexterity();

		damage -= target->getConstitution() / 2.0f;

		if (damage < 7.0f)
		{
			damage = 7.0f;
		}

		std::cout << "* " << target->getName() << " is bleeding *" << std::endl;

		target->decreaseHealth(damage);
	}
}

void DebuffBleeding::removeEffectCheck()
{
	return;
}

void DebuffBleeding::restartDuration()
{
	this->duration = 4;
}
