#include "Chimera.hpp"

//Constructor

Chimera::Chimera(std::string name, std::string faction, std::string race, float strength, float agility, float constitution, float intelligence, float dexterity, float lucky, int exp) :
	NpCharacter(name, faction, race, strength, agility, constitution, intelligence, dexterity, lucky, exp)
{
	this->bag = createNpcBag();
	calculateCombatStatus();
}

//Creator

Chimera* Chimera::createEnemy()
{
	return new Chimera("Ancient Quimera", "Unknown", "Beast", 25.0f, 20.0f, 80.0f, 3.0f, 20.0f, 20.0f, 493);

}

Bag* Chimera::createNpcBag()
{
	std::vector<Item*> npcItems;
	return new Bag(10, npcItems);
}

//Skills Sets

void Chimera::npcSkillSet(std::vector <Character*> players)
{
	std::cout << "- " << this->getName() << "'s turn -" << std::endl;

	size_t target = chooseEnemy(players);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	int chance = dis(gen);

	if (chance >= 1 && chance < 20)
	{
		this->basicAttack(players[target]);
	}
	else if (chance >= 21 && chance < 40)
	{
		this->bite(players[target]);
	}
	else if (chance >= 41 && chance <= 50)
	{
		this->clawStrike(players[target]);
	}
	else if (chance >= 51 && chance < 65)
	{
		std::cout << std::endl;
		std::cout << "* The goat and the snake attacked together *" << std::endl;
		std::cout << std::endl;

		this->basicAttack(players[target]);
		this->bite(players[target]);
	}
	else if (chance >= 66 && chance < 75)
	{
		std::cout << std::endl;
		std::cout << "* The lion and the goat attacked together *" << std::endl;
		std::cout << std::endl;

		this->clawStrike(players[target]);
		this->basicAttack(players[target]);
	}
	else if (chance >= 76 && chance <= 90)
	{
		std::cout << std::endl;
		std::cout << "* The lion and the snake attacked together *" << std::endl;
		std::cout << std::endl;

		this->clawStrike(players[target]);
		this->bite(players[target]);
	}
	else if (chance >= 91 && chance < 100)
	{
		std::cout << std::endl;
		std::cout << "* All three heads attacked together " << std::endl;
		std::cout << std::endl;

		this->basicAttack(players[target]);
		this->bite(players[target]);
		this->clawStrike(players[target]);
	}

}