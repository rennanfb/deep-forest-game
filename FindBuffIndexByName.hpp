#pragma once
#include <vector>
#include <string>
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Buff.hpp"

class Buff;
class Character;
class NpCharacter;

int FindBuffIndexByName(const std::vector<Buff*>& buffList, const std::string& nameToFind);