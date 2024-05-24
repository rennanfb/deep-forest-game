#include "Interval.hpp"

void Interval(Character* player1) 
{
	player1->healStats();
	player1->showSheet();

	std::cout << "Continue ? (Enter Y for Yes)" << std::endl;
	std::string answer;
	std::cin >> answer;

	if (answer == "Y" || answer == "y") 
	{
		return;
	}
	else
	{
		Interval(player1);
	}
}