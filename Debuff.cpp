#include "Debuff.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

Debuff::Debuff(std::string name, Creature* user, Creature* target, int duration) :
	name(name),
	user(user),
	target(target),
	duration(duration)
{

}

void Debuff::decreaseDuration()
{
	this->duration -= 1;
}

std::string Debuff::getName()
{
	return name;
}

int Debuff::getDuration()
{
	return duration;
}