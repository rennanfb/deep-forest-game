#include "Act1.hpp"
#include "Act2.hpp"
#include "Act3.hpp"

int main() 
{
	std::cout << std::setprecision(0) << std::fixed;

	Character* player = CharacterCreation();
	std::vector<Character*> players = { player };

	Act1(players);

	Act2(players);
	
	Character* luna = Priest::createCharacter("Luna", "Sundeva", "Human");
	players.push_back(luna);

	Act3(players);

}