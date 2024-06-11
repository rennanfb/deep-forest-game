#pragma once
#include "Item.hpp"
#include "Character.hpp"

class PotionLarge : public Item
{
protected:

	static int itemAmount;
	float energyAmount;

public:

	//Constructor

	PotionLarge(std::string itemName, std::string itemDescription, float energyAmount);

	//Destructor

	~PotionLarge();

	//Creator

	static PotionLarge* createItem();

	//General Methods

	void use(Character* player) override;

	//Getters

	int getItemAmount() override;

};
