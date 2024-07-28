#pragma once
#include <vector>
#include <string>
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Debuff.hpp"

class Debuff;
class Character;
class NpCharacter;

int FindDebuffIndexByName(const std::vector<Debuff*>& debuffList, const std::string& nameToFind);