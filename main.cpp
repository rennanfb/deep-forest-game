#include "Act1.hpp"
#include "Act2.hpp"
#include "Act3.hpp"

int main() 
{
	std::cout << std::setprecision(0) << std::fixed;

	// First Act
	Character* player = CharacterCreation();
	std::vector<Character*> players = { player };
	Act1(players);

	// Second Act
	Character* luna = nullptr;
	Act2(players, luna);

	// Third Act
	Character* qing = nullptr;
	Act3(players, qing);
}
