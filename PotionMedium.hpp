#pragma once
#include "Item.hpp"
#include "Character.hpp"

class PotionMedium : public Item
{
protected:

	static int itemAmount;
	float energyAmount;

public:

	//Constructor

	PotionMedium(std::string itemName, std::string itemDescription, float energyAmount);

	//Destructor

	~PotionMedium();

	//Creator

	static PotionMedium* createItem();

	//General Methods

	void use(Character* player) override;

	//Getters

	int getItemAmount() override;

};
