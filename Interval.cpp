#include "Interval.hpp"

void Interval(std::vector <Character*> players) 
{
	for (size_t i = 0; i < players.size(); ++i)
	{
		players[i]->healStats();
		players[i]->showSheet();
	}

	std::cout << "Continue ? (Enter Y for Yes)" << std::endl;
	std::string answer;
	std::cin >> answer;

	if (answer == "Y" || answer == "y") 
	{
		return;
	}
	else
	{
		Interval(players);
	}
}