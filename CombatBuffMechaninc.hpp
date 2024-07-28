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

void CombatBuffMechanic(NpCharacter* enemy);

void CombatBuffMechanic(Character* player);