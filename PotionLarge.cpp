#include "PotionLarge.hpp"

int PotionLarge::itemAmount = 0;

//Constructor

PotionLarge::PotionLarge(std::string itemName, std::string itemDescription, float energyAmount) :
	Item(itemName, itemDescription),
	energyAmount(energyAmount)
{
	this->itemAmount++;
}

//Destructor

PotionLarge::~PotionLarge()
{
	if (itemAmount > 0)
	{
		itemAmount--;
	}
}

//Creator

PotionLarge* PotionLarge::createItem()
{
	return new PotionLarge("Small Potion", "Restores a large amount of energy (Fury, Stamina, Mana)", 90.0f);
}

//General Meethods

void PotionLarge::use(Character* player)
{
	player->restoreEnergy(this->energyAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Large Potion and recovered " << this->energyAmount << " points of combat energy" << std::endl;
	std::cout << std::endl;
}

//Getters

int PotionLarge::getItemAmount()
{
	return itemAmount;
}
