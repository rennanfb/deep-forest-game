#include "FindBuffIndexByName.hpp"
#include "Buff.hpp"
#include "Character.hpp"
#include "NpCharacter.hpp"

int FindBuffIndexByName(const std::vector<Buff*>& buffList, const std::string& nameToFind)
{
	auto it = std::find_if(buffList.begin(), buffList.end(), [&nameToFind](Buff* buff)
		{
			return buff->getName() == nameToFind;
		});
	return (it != buffList.end()) ? std::distance(buffList.begin(), it) : -1;
}