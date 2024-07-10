#include "Act1.hpp"
#include "Act2.hpp"

int main() 
{
	std::cout << std::setprecision(0) << std::fixed;

	Character* player1 = CharacterCreation();
	std::vector<Character*> players = { player1 };

	Act1(players);

	Act2(players);
	
	//Character* luna = CompanionPriest::createCharacter("Luna", "Sundeva", "Human");
	//players.push_back(luna);


}