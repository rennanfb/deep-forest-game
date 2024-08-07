#include "Act3.hpp"

void Act3(std::vector <Character*>& players, Character*& qing)
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

	NpCharacter* enemy6 = Chimera::createEnemy();
	std::vector<NpCharacter*> enemies2 = { enemy6 };
	Conflict10(players, enemies2);
	enemies2.clear();
	Interval(players);

	qing = Hunter::createQing(3);
	qing->checkLevelAttributes();
	players.push_back(qing);

	NpCharacter* enemy7 = InjuriedSeiren::createEnemy();
	NpCharacter* enemy8 = GoblinWarlock::createEnemy();
	NpCharacter* enemy9 = GoblinWarlock::createEnemy();
	std::vector<NpCharacter*> enemies3 = { enemy7, enemy8, enemy9 };
	Conflict11(players, enemies3);
	enemies3.clear();
	Interval(players);
}