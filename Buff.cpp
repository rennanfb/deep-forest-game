#include "Buff.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

Buff::Buff(Character* player, NpCharacter* npc, int duration) :
	player(player),
	npc(npc),
	duration(duration)
{

}

void Buff::decreaseDuration() 
{
	this->duration -= 1;
}