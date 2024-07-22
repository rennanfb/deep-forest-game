#include "CharacterCreation.hpp"

Character* CharacterCreation() 
{

	std::cout << "What is your name? " << std::endl;
	std::string charName;
	std::getline(std::cin, charName);

	std::string raceName = Creature::setRace();

	std::cout << "Which is your job?" << std::endl;
	std::cout << "Enter (1) - Warrior" << std::endl;
	std::cout << "Enter (2) - Rogue" << std::endl;
	std::cout << "Enter (3) - Mage" << std::endl;
	std::cout << "Enter (4) - Hunter" << std::endl;
	std::cout << "Enter (5) - Priest" << std::endl;

	std::string classChoice;
	std::cin >> classChoice;

	if (classChoice == "1") 
	{
		Character* player1 = Warrior::createCharacter(charName, "Nomad", raceName);
		player1->raceBonus(raceName);
		return player1;
	}
	else if (classChoice == "2") 
	{
		Character* player1 = Rogue::createCharacter(charName, "Nomad", raceName);
		player1->raceBonus(raceName);
		return player1;
	}
	else if (classChoice == "3") 
	{
		Character* player1 = Mage::createCharacter(charName, "Nomad", raceName);
		player1->raceBonus(raceName);
		return player1;
	}
	else if (classChoice == "4")
	{
		Character* player1 = Hunter::createCharacter(charName, "Nomad", raceName);
		player1->raceBonus(raceName);
		return player1;
	}
	else if (classChoice == "5")
	{
		Character* player1 = Priest::createCharacter(charName, "Nomad", raceName);
		player1->raceBonus(raceName);
		return player1;
	}
	else 
	{
		std::cout << "You had to enter the class number as the exemple (1 - Warrior | 2 - Rogue | 3 - Mage)" << std::endl;
		return CharacterCreation();
	}

}


