#include "Bag.hpp"
#include "Character.hpp"

Bag::Bag(int slots, std::vector<Item*> items) :
	slots(slots),
	items(items)
{

}

Bag* Bag::createInitialBag() 
{
	std::vector<Item*> initialItens;
	initialItens.push_back(ElixirSmall::createItem());
	initialItens.push_back(PotionSmall::createItem());

	return new Bag(10, initialItens);
}

void Bag::showBagLayout(std::vector<NpCharacter*> enemies, Character* player)
{
	std::cout << "---------------------------------------------------------------------------------" << std::endl;
	std::cout << "Bag itens: " << std::endl;
	
	std::map<std::string, std::pair<int, std::string>> itemCounts;

	for (Item* item : items)
	{
		std::string itemName = item->getItemName();
		std::string itemDescription = item->getItemDescription();

		if (itemCounts.find(itemName) != itemCounts.end())
		{
			itemCounts[itemName].first++;
		}
		else
		{
			itemCounts[itemName] = std::make_pair(1, itemDescription);
		}
	}

	int index = 1;
	for (const auto& pair : itemCounts) 
	{
		std::cout << index++ << " - " << pair.first << " " << pair.second.first << "x | " << pair.second.second << std::endl;
	}

	std::cout << "---------------------------------------------------------------------------------" << std::endl;

	std::cout << std::endl;
	std::cout << "- Enter the number of the item to use it, or Enter (0) to return -" << std::endl;

	int answer;
	std::cin >> answer;

	if (answer >= 1 && answer <= items.size())
	{
		items[answer - 1]->use(player);
		delete player->bag->items[answer - 1];
		items.erase(items.begin() + (answer - 1));
		player->showCombatLayout(enemies);

	}
	else if (answer == 0)
	{
		player->showCombatLayout(enemies);
	}
	else
	{
		std::cout << "invalid value, Enter the number of the item" << std::endl;
		showBagLayout(enemies, player);
	}

}

void Bag::showBag()
{
	std::cout << "---------------------------------------------------------------------------------" << std::endl;

	std::cout << "Bag itens: " << std::endl;

	std::map<std::string, std::pair<int, std::string>> itemCounts;

	for (Item* item : items)
	{
		std::string itemName = item->getItemName();
		std::string itemDescription = item->getItemDescription();

		if (itemCounts.find(itemName) != itemCounts.end())
		{
			itemCounts[itemName].first++;
		}
		else
		{
			itemCounts[itemName] = std::make_pair(1, itemDescription);
		}
	}

	int index = 1;
	for (const auto& pair : itemCounts)
	{
		std::cout << index++ << " - " << pair.first << " " << pair.second.first << "x | " << pair.second.second << std::endl;
	}
	std::cout << "---------------------------------------------------------------------------------" << std::endl;
}

void Bag::addItem(std::vector<Item*> droppedItems)
{
	if (this->items.size() < this->slots)
	{
		for (size_t i = 0; i < droppedItems.size(); ++i)
		{
			this->items.push_back(droppedItems[i]);
		}
	}
	else
	{
		std::cout << "The bag is full" << std::endl;
	}
}

std::vector<Item*> Bag::getBagItems() 
{
	return this->items;
}
