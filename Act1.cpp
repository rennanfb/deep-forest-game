#include "Act1.hpp"

void Act1(Character* player1) 
{
	Interval(player1);

	NpCharacter* enemy1 = GoblinRebel::createEnemy();
	std::vector<NpCharacter*> enemies = { enemy1 };
	Conflict1(player1, enemies);

	Interval(player1);

	NpCharacter* enemy2 = GoblinWarrior::createEnemy();
	std::vector<NpCharacter*> enemies2 = { enemy2 };
	Conflict2(player1, enemies2);

	Interval(player1);

	NpCharacter* enemy3 = GoblinPaladin::createEnemy();
	std::vector<NpCharacter*> enemies3 = { enemy3 };
	Conflict3(player1, enemies3);

	Interval(player1);

	NpCharacter* enemy4 = GoblinZombie::createEnemy();
	NpCharacter* enemy5 = TorturerZulmin::createEnemy();
	std::vector<NpCharacter*> enemies4 = { enemy4, enemy5 };
	Conflict4(player1, enemies4);
}