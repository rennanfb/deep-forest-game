#pragma once
#include <iostream>
#include "Warrior.hpp"
#include "Rogue.hpp"
#include "Mage.hpp"
#include "Hunter.hpp"
#include "Priest.hpp"
#include "NpCharacter.hpp"
#include "Buff.hpp"
#include "BuffBlessed.hpp"
#include "DebuffBurning.hpp"
#include "DebuffBleeding.hpp"
#include "DebuffPoisoned.hpp"
#include "CombatBuffMechaninc.hpp"
#include "CombatDebuffMechanic.hpp"

void Conflict8(std::vector <Character*> players, std::vector<NpCharacter*> enemies);