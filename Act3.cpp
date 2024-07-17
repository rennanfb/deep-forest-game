#include "Act3.hpp"

void Act3(std::vector <Character*> players)
{
	Interval(players);

	NpCharacter* enemy1 = SaberwolfAlpha::createEnemy();
	NpCharacter* enemy2 = Saberwolf::createEnemy();
	NpCharacter* enemy3 = Saberwolf::createEnemy();
	NpCharacter* enemy4 = Saberwolf::createEnemy();
	NpCharacter* enemy5 = Saberwolf::createEnemy();

	std::vector<NpCharacter*> enemies = { enemy1, enemy2, enemy3, enemy4, enemy5 };
	Conflict9(players, enemies);
	enemies.clear();

	Interval(players);

}