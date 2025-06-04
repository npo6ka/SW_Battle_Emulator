#pragma once

#include "Features/Units/Unit.hpp"

namespace sw::game
{

	class Hunter : public Unit
	{
	public:
		Hunter(
			unsigned int id,
			int hp,
			const Position& pos,
			unsigned int agility,
			unsigned int strength,
			unsigned int range);

		std::string getType() const override
		{
			return "Hunter";
		}
	};

}
