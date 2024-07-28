#pragma once
#include <vector>
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "Buff.hpp"
#include "BuffBlessed.hpp"
#include "Debuff.hpp"
#include "DebuffBleeding.hpp"
#include "DebuffBurning.hpp"
#include "DebuffPoisoned.hpp"

void CombatDebuffMechanic(NpCharacter* enemy);

void CombatDebuffMechanic(Character* player);