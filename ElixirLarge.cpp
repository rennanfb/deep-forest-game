#include "ElixirLarge.hpp"

int ElixirLarge::itemAmount = 0;

//Constructor

ElixirLarge::ElixirLarge(std::string itemName, std::string itemDescription, float healingAmount) :
	Item(itemName, itemDescription),
	healingAmount(healingAmount)
{
	this->itemAmount++;
}

//Destructor

ElixirLarge::~ElixirLarge()
{
	if (itemAmount > 0)
	{
		itemAmount--;
	}
}

//Creator

ElixirLarge* ElixirLarge::createItem()
{
	return new ElixirLarge("Small Elixir", "Restores a large amount of health", 130.0f);
}

//General Methods

void ElixirLarge::use(Character* player)
{
	player->restoreHealth(this->healingAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Large Elixir and recovered " << this->healingAmount << " points of health" << std::endl;
	std::cout << std::endl;
}

//Getters

int ElixirLarge::getItemAmount()
{
	return itemAmount;
}