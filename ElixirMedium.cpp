#include "ElixirMedium.hpp"

int ElixirMedium::itemAmount = 0;

//Constructor

ElixirMedium::ElixirMedium(std::string itemName, std::string itemDescription, float healingAmount) :
	Item(itemName, itemDescription),
	healingAmount(healingAmount)
{
	this->itemAmount++;
}

//Destructor

ElixirMedium::~ElixirMedium()
{
	if (itemAmount > 0)
	{
		itemAmount--;
	}
}

//Creator

ElixirMedium* ElixirMedium::createItem()
{
	return new ElixirMedium("Small Elixir", "Restores a medium amount of health", 100.0f);
}

//General Methods

void ElixirMedium::use(Character* player)
{
	player->restoreHealth(this->healingAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Medium Elixir and recovered " << this->healingAmount << " points of health" << std::endl;
	std::cout << std::endl;
}

//Getters

int ElixirMedium::getItemAmount()
{
	return itemAmount;
}