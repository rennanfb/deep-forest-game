#include "FindDebuffIndexByName.hpp"
#include "Debuff.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

int FindDebuffIndexByName(const std::vector<Debuff*>& debuffList, const std::string& nameToFind)
{
	auto it = std::find_if(debuffList.begin(), debuffList.end(), [&nameToFind](Debuff* debuff)
		{
			return debuff->getName() == nameToFind;
		});
	return (it != debuffList.end()) ? std::distance(debuffList.begin(), it) : -1;
}