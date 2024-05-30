#include "Act2.hpp"

void Act2(Character* player1)
{
	Interval(player1);

	NpCharacter* enemy1 = EgoShadow::createEnemy();
	std::vector<NpCharacter*> enemies = { enemy1 };
	Conflict5(player1, enemies);

	Interval(player1);

	NpCharacter* enemy2 = GnomeRath::createEnemy();
	NpCharacter* enemy3 = GnomeBeth::createEnemy();
	std::vector<NpCharacter*> enemies2 = { enemy2, enemy3 };
	Conflict6(player1, enemies2);

	Interval(player1);

	NpCharacter* enemy4 = BoarColossal::createEnemy();
	std::vector<NpCharacter*> enemies3 = { enemy4 };
	Conflict7(player1, enemies3);

	Interval(player1);

	Character* companion = CompanionPriest::createCharacter("Priestess of the Sun", "Sundeva", "Human");
	NpCharacter* enemy5 = DemonAztras::createEnemy();
	NpCharacter* enemy6 = GoblinPaladin::createEnemy();
	NpCharacter* enemy7 = GoblinPaladin::createEnemy();
	std::vector<NpCharacter*> enemies4 = { enemy5, enemy6, enemy7 };
	Conflict8(player1, companion, enemies4);

}