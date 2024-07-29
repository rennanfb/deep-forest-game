#include "DebuffStunned.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

DebuffStunned::DebuffStunned(std::string name, Creature* user, Creature* target, int duration) :
	Debuff(name, user, target, duration)
{

}

DebuffStunned* DebuffStunned::create(Creature* user, Creature* target)
{
	return new DebuffStunned("Stunned", user, target, 1);
}

void DebuffStunned::applyEffect()
{
	target->disableCreature();
	std::cout << "* " << target->getName() << " is stunned *" << std::endl;
}

void DebuffStunned::removeEffectCheck()
{
	target->activateCreature();
	return;
}

void DebuffStunned::restartDuration()
{
	this->duration = 1;
}



