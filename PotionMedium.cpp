#include "PotionMedium.hpp"

int PotionMedium::itemAmount = 0;

//Constructor

PotionMedium::PotionMedium(std::string itemName, std::string itemDescription, float energyAmount) :
	Item(itemName, itemDescription),
	energyAmount(energyAmount)
{
	this->itemAmount++;
}

//Destructor

PotionMedium::~PotionMedium()
{
	if (itemAmount > 0)
	{
		itemAmount--;
	}
}

//Creator

PotionMedium* PotionMedium::createItem()
{
	return new PotionMedium("Small Potion", "Restores a medium amount of energy (Fury, Stamina, Mana)", 60.0f);
}

//General Methods

void PotionMedium::use(Character* player)
{
	player->restoreEnergy(this->energyAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Medium Potion and recovered " << this->energyAmount << " points of combat energy" << std::endl;
	std::cout << std::endl;
}

//Getters

int PotionMedium::getItemAmount()
{
	return itemAmount;
}