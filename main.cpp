#include <iostream>
#include "Creature.hpp"
#include "Character.hpp"
#include "CharacterCreation.hpp"
#include "Warrior.hpp"
#include "Mage.hpp"
#include "Rogue.hpp"
#include "NpCharacter.hpp"
#include "Goblin.hpp"
#include "Interval.hpp"
#include "FirstConflict.hpp"
#include "SecondConflict.hpp"
#include "ThirdConflict.hpp"
#include "FourthConflict.hpp"

int main() 
{
	Character* player1 = CharacterCreation();

	Interval(player1);

	NpCharacter* enemy1 = Goblin::createEnemy(1);
	FirstConflict(player1, enemy1);

	Interval(player1);

	NpCharacter* enemy2 = Goblin::createEnemy(2);
	SecondConflict(player1, enemy2);

	Interval(player1);

	NpCharacter* enemy3 = Goblin::createEnemy(3);
	ThirdConflict(player1, enemy3); 

	Interval(player1);

	NpCharacter* enemy4 = Goblin::createEnemy(4);
	NpCharacter* enemy5 = Goblin::createEnemy(5);
	FourthConflict(player1, enemy4, enemy5);

	Interval(player1);

}