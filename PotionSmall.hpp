#pragma once
#include "Item.hpp"
#include "Character.hpp"

class PotionSmall : public Item
{
protected:

	static int itemAmount;
	float energyAmount;

public:

	//Constructor

	PotionSmall(std::string itemName, std::string itemDescription, float energyAmount);

	//Destructor

	~PotionSmall();

	//Creator

	static PotionSmall* createItem();

	//General Methods

	void use(Character* player) override;

	//Getters

	int getItemAmount() override;

};
