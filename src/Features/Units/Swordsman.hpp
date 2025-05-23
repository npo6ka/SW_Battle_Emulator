#pragma once

#include "Core/Unit/Unit.hpp"

namespace sw::game
{

	class Swordsman : public Unit
	{
	public:
		Swordsman(unsigned int id, int hp, unsigned int strength, const Position& pos = Position());

		std::string getType() const override
		{
			return "Swordsman";
		}
	};

}
