#include "Act1.hpp"
#include "Act2.hpp"

int main() 
{
	std::cout << std::setprecision(0) << std::fixed;

	Character* player1 = CharacterCreation();

	Act1(player1);

	Act2(player1);

}