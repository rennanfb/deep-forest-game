#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "Item.hpp"
#include "Creature.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"
#include "ElixirSmall.hpp"
#include "ElixirMedium.hpp"
#include "ElixirLarge.hpp"
#include "PotionSmall.hpp"
#include "PotionMedium.hpp"
#include "PotionLarge.hpp"

class Character;

class Bag
{
protected:

	int slots;
	std::vector<Item*> items;

public:

	//Constructor

	Bag(int slots, std::vector<Item*> items);

	//Creator

	static Bag* createInitialBag();

	//Layout Methods

	void showBagLayout(Character* player);
	void showBag();

	//General Methods

	void addItem(std::vector<Item*> items);

	//Getters

	std::vector<Item*> getBagItems();
};

