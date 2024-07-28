#include "BuffBlessed.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

BuffBlessed::BuffBlessed(std::string name, Creature* user, Creature* target, int duration) :
	Buff(name, user, target, duration)
{
}

BuffBlessed* BuffBlessed::create(Creature* user, Creature* target)
{
	return new BuffBlessed("Blessing", user, target, 5);
}

void BuffBlessed::applyEffect()
{
	std::cout << this->target->getName() << " is Blessed" << std::endl;

	if (this->duration == 5 && !buffApplied) 
	{
		originalStrength = target->getStrength();
		originalConstitution = target->getConstitution();
		originalLucky = target->getLucky();

		target->upStrength(user->getIntelligence() / 3);
		target->upConstitution(user->getIntelligence() / 3);
		target->upLucky(user->getIntelligence() / 2);

		buffApplied = true;
	}

	return;
}

void BuffBlessed::removeEffectCheck()
{
	if (this->duration <= 0) 
	{
		target->setStrength(originalStrength);
		target->setConstitution(originalConstitution);
		target->setLucky(originalLucky);

		buffApplied = false;
	}
}

void BuffBlessed::restartDuration()
{
	this->duration = 5;
}

