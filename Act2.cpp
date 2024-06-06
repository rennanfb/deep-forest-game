#include "Act2.hpp"

void Act2(std::vector <Character*> players)
{
	Interval(players);

	NpCharacter* enemy1 = EgoShadow::createEnemy();
	std::vector<NpCharacter*> enemies = { enemy1 };
	Conflict5(players, enemies);

	Interval(players);

	NpCharacter* enemy2 = GnomeRath::createEnemy();
	NpCharacter* enemy3 = GnomeBeth::createEnemy();
	std::vector<NpCharacter*> enemies2 = { enemy2, enemy3 };
	Conflict6(players, enemies2);

	Interval(players);

	NpCharacter* enemy4 = BoarColossal::createEnemy();
	std::vector<NpCharacter*> enemies3 = { enemy4 };
	Conflict7(players, enemies3);

	Interval(players);

	Character* luna = CompanionPriest::createCharacter("Priestess of the Sun", "Sundeva", "Human");
	players.push_back(luna);

	NpCharacter* enemy5 = DemonAztras::createEnemy();
	NpCharacter* enemy6 = GoblinPaladin::createEnemy();
	NpCharacter* enemy7 = GoblinPaladin::createEnemy();
	std::vector<NpCharacter*> enemies4 = { enemy5, enemy6, enemy7 };
	Conflict8(players, enemies4);

}