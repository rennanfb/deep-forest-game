#pragma once
#include <string>
#include "Character.hpp"

class Item
{
protected:
	std::string itemName;
	std::string itemDescription;
public:

	//Constructor

	Item(std::string itemName, std::string itemDescription);

	//Pure Virtual Methods

	virtual void use(Character* player) = 0;
	virtual int getItemAmount() = 0;

	//Getters

	std::string getItemName();
	std::string getItemDescription();

};

