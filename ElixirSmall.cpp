#include "ElixirSmall.hpp"

int ElixirSmall::itemAmount = 0;

//Constructor

ElixirSmall::ElixirSmall(std::string itemName, std::string itemDescription, float healingAmount) :
	Item(itemName, itemDescription),
	healingAmount(healingAmount)
{
	this->itemAmount++;
}

//Destructor

ElixirSmall::~ElixirSmall()
{
	if (itemAmount > 0)
	{
		itemAmount--;
	}
}

//Creator

ElixirSmall* ElixirSmall::createItem()
{
	return new ElixirSmall("Small Elixir", "Restores a small amount of health", 70.0f);
}

//General Methods

void ElixirSmall::use(Character* player)
{
	player->restoreHealth(this->healingAmount);
	std::cout << std::endl;
	std::cout << player->getName() << " used Small Elixir and recovered " << this->healingAmount << " points of health" << std::endl;
	std::cout << std::endl;
}

//Getters

int ElixirSmall::getItemAmount()
{
	return itemAmount;
}