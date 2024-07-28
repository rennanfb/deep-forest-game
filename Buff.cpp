#include "Buff.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

Buff::Buff(std::string name, Creature* user, Creature* target, int duration) :
	name(name),
	user(user),
	target(target),
	duration(duration)
{

}

void Buff::decreaseDuration() 
{
	this->duration -= 1;
}

std::string Buff::getName()
{
	return name;
}

int Buff::getDuration()
{
	return duration;
}
