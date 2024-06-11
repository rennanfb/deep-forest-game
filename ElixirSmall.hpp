#pragma once
#include "Item.hpp"
#include "Character.hpp"

class ElixirSmall : public Item
{
protected:

	static int itemAmount;
	float healingAmount;

public:

	//Constructor

	ElixirSmall(std::string itemName, std::string itemDescription, float healingAmount);

	//Destructor

	~ElixirSmall();

	//Creator

	static ElixirSmall* createItem();

	//General Methods

	void use(Character* player) override;
	
	//Getters

	int getItemAmount() override;
};

