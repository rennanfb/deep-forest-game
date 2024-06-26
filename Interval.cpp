#include "Interval.hpp"

void Interval(std::vector <Character*> players) 
{
	for (size_t i = 0; i < players.size(); ++i)
	{
		players[i]->healStats();
		players[i]->showSheet();
	}

	std::cout << "Continue ? (Enter Y for Yes) | Check you bag ? (Enter B)" << std::endl;
	std::string answer;
	std::cin >> answer;

	if (answer == "Y" || answer == "y") 
	{
		return;
	}
	else if (answer == "B" || answer == "b")
	{
		players[0]->bag->showBag();
		Interval(players);
	}
	else
	{
		std::cout << "Enter a valid answer: (Y) To continue the game | (B) To see the bag" << std::endl;
		Interval(players);
	}
}