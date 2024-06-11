#pragma once
#include "Item.hpp"
#include "Character.hpp"

class ElixirMedium : public Item
{
protected:

	static int itemAmount;
	float healingAmount;

public:

	//Constructor

	ElixirMedium(std::string itemName, std::string itemDescription, float healingAmount);

	//Destructor

	~ElixirMedium();

	//Creator

	static ElixirMedium* createItem();

	//General Methods

	void use(Character* player) override;

	//Getters

	int getItemAmount() override;
};

