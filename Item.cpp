#include "Item.hpp"

//Constructor

Item::Item(std::string itemName, std::string itemDescription) :
	itemName(itemName),
	itemDescription(itemDescription)
{

}

//Getters

std::string Item::getItemName() 
{
	return this->itemName;
}

std::string Item::getItemDescription()
{
	return this->itemDescription;
}