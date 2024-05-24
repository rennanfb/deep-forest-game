#include "CharacterCreation.hpp"

Character* CharacterCreation() 
{

	std::cout << "What is your name? " << std::endl;
	std::string charName;
	std::cin >> charName;
	std::cout << "What Faction do you serve?" << std::endl;
	std::string factionName;
	std::cin >> factionName;
	std::cout << "What is your race?" << std::endl;
	std::string raceName;
	std::cin >> raceName;
	std::cout << "Write your job: (Warrior, Rogue or Mage)" << std::endl;
	std::string classChoice;
	std::cin >> classChoice;

	if (classChoice == "Warrior") 
	{
		Warrior* player1 = Warrior::createCharacter(charName, factionName, raceName);
		return player1;
	}
	if (classChoice == "Rogue") 
	{
		Rogue* player1 = Rogue::createCharacter(charName, factionName, raceName);
		return player1;
	}
	if (classChoice == "Mage") 
	{
		Mage* player1 = Mage::createCharacter(charName, factionName, raceName);
		return player1;
	}
	else 
	{
		std::cout << "You had to write the class name as the exemple (Warrior, Rogue or Mage)" << std::endl;
		return CharacterCreation();
	}
}


