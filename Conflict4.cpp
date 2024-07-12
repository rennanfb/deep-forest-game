#include "Conflict4.hpp"

void Conflict4(std::vector <Character*> players, std::vector<NpCharacter*> enemies)
{
	std::cout << std::endl;
	std::cout << "------------------------------- Is he alive? -------------------------------" << std::endl;
	std::cout << "The dark paladin is dead, his body goes down the river he fell, this place is" << std::endl;
	std::cout << "dangerous, something is happening nearby with these goblins." << std::endl;
	std::cout << "You notice that he seemed to eat a lot, it could be a good ideia to go look" << std::endl;
	std::cout << "for food from the place they came, it could help to hang the trip, the problem is" << std::endl;
	std::cout << "that other creepy cold goblin must be there, but you had already killed three " << std::endl;
	std::cout << "of them, if anything goes wrong, you'll handle it" << std::endl;
	std::cout << "while approaching the campsite, you notice that is a very small camp with only" << std::endl;
	std::cout << "one tent, you can hear strange noises coming from inside." << std::endl;
	std::cout << "Next to the tent entrace, you see the creepy goblin torturing the carcass of" << std::endl;
	std::cout << "the first goblin you killed, and the worst, he seems to be alive again." << std::endl;
	std::cout << "What kind of evil sorcery is this... necromancy? it must be why the first" << std::endl;
	std::cout << "goblin was hidding alone, he was been chased for the worst kind of questioning" << std::endl;
	std::cout << "how could someone use dark sorcery to torture a dead soul for answers? that goblin" << std::endl;
	std::cout << "should know something very important." << std::endl;
	std::cout << "With what you just saw, and with no time to recompose yourself, you hear..." << std::endl;
	std::cout << std::endl;
	std::cout << "Torturer Zulmin: will you stay with this ugly face in this entrace for how long?" << std::endl;
	std::cout << std::endl;
	std::cout << "this creepy goblin can talk your language, but now is not a good moment to talk" << std::endl;
	std::cout << "you should just get some food and go but, this all was so unsettling" << std::endl;
	std::cout << std::endl;
	std::cout << "Torturer Zulmin: I really hate these appostates, but theres a thing i hate more..." << std::endl;
	std::cout << "your kind... i will alow him to feast revenge upon you" << std::endl;
	std::cout << std::endl;

	while (players[0]->isAlive() && (enemies[0]->isAlive() || enemies[1]->isAlive()))
	{
		for (size_t i = 0; i < enemies.size(); ++i) {
			if (enemies[i]->isAlive())
			{
				enemies[i]->npcSkillSet(players);
			}
		}

		if (players[0]->isAlive())
		{
			players[0]->showCombatLayout(enemies);
		}

	}

	if (!enemies[0]->isAlive() && !enemies[1]->isAlive())
	{
		players[0]->defeatEnemy(enemies[0]);
		players[0]->defeatEnemy(enemies[1]);

		std::cout << std::endl;
		std::cout << "While the zombie goblin's soul are fading down to the ground, you can see " << std::endl;
		std::cout << "that something like that is leaving your body too, and for a moment, you hear" << std::endl;
		std::cout << "a whisper that even without understand the language, it put you to sleep" << std::endl;

	}
	else if (!players[0]->isAlive())
	{
		std::cout << players[0]->getName() << " fall down" << std::endl;
		std::cout << "You'are dead" << std::endl;
		delete players[0];
		exit(0);
	}


}