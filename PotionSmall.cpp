#include "PotionSmall.hpp"

int PotionSmall::itemAmount = 0;

//Constructor

PotionSmall::PotionSmall(std::string itemName, std::string itemDescription, float energyAmount) :
	Item(itemName, itemDescription),
	energyAmount(energyAmount)
{
	this->itemAmount++;
}

//Destructor

PotionSmall::~PotionSmall()
{
	if (itemAmount > 0) 
	{
		itemAmount--;
	}
}

//Creator

PotionSmall* PotionSmall::createItem()
{
	return new PotionSmall("Small Potion", "Restores a small amount of energy (Fury, Stamina, Mana)", 30.0f);
}

//General Methods

void PotionSmall::use(Character* player)
{
	player->restoreEnergy(this->energyAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Small Potion and recovered " << this->energyAmount << " points of combat energy" << std::endl;
	std::cout << std::endl;
}

//Getters

int PotionSmall::getItemAmount()
{
	return itemAmount;
}
