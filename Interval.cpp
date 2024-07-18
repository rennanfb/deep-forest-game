#include "Interval.hpp"

void Interval(std::vector <Character*> players) 
{
	std::cout << "------------------ Party ------------------" << std::endl;
	for (Character* player : players)
	{
		player->healStats();
		player->showSheet();
	}
	std::cout << "-------------------------------------------" << std::endl;

	std::cout << "Continue ? (Enter Y for Yes) | Check you bag ? (Enter B)" << std::endl;
	std::string answer;
	std::cin >> answer;

	if (answer == "Y" || answer == "y") 
	{
		return;
	}
	else if (answer == "B" || answer == "b")
	{
		if (players.size() > 1)
		{
			std::cout << "Whose bag do you want to see?" << std::endl;

			int i = 1;
			for (Character* player : players)
			{
				std::cout << player->getName() << " - Enter (" << i << ")" << std::endl;
				++i;
			}
			int intAnswer;
			std::cin >> intAnswer;

			std::cout << "Showing " << players[intAnswer - 1]->getName() << "'s bag:" << std::endl;
			players[intAnswer - 1]->bag->showBag();
			Interval(players);

		}
		else
		{
			players[0]->bag->showBag();
			Interval(players);
		}
	}
	else
	{
		std::cout << "Enter a valid answer: (Y) To continue the game | (B) To see the bag" << std::endl;
		Interval(players);
	}
}