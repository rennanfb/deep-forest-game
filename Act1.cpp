#include "Act1.hpp"

void Act1(std::vector <Character*> players) 
{
	Interval(players);

	NpCharacter* enemy1 = GoblinRebel::createEnemy();
	std::vector<NpCharacter*> enemies = { enemy1 };
	
	Conflict1(players, enemies);
	enemies.clear();
	Interval(players);

	NpCharacter* enemy2 = GoblinWarrior::createEnemy();
	std::vector<NpCharacter*> enemies2 = { enemy2 };
	
	Conflict2(players, enemies2);
	enemies2.clear();
	Interval(players);

	NpCharacter* enemy3 = GoblinPaladin::createEnemy();
	std::vector<NpCharacter*> enemies3 = { enemy3 };
	
	Conflict3(players, enemies3);
	enemies3.clear();
	Interval(players);

	NpCharacter* enemy4 = GoblinZombie::createEnemy();
	NpCharacter* enemy5 = TorturerZulmin::createEnemy();
	std::vector<NpCharacter*> enemies4 = { enemy4, enemy5 };
	
	Conflict4(players, enemies4);
	enemies4.clear();
}