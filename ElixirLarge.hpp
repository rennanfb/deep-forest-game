#pragma once
#include "Item.hpp"
#include "Character.hpp"

class ElixirLarge : public Item
{
protected:

	static int itemAmount;
	float healingAmount;

public:

	//Constructor

	ElixirLarge(std::string itemName, std::string itemDescription, float healingAmount);

	//Destructor

	~ElixirLarge();

	//Creator

	static ElixirLarge* createItem();

	//General Methods

	void use(Character* player) override;

	//Getters

	int getItemAmount() override;
};

