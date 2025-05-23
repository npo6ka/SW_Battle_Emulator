#pragma once

#include "Core/Unit/UnitStats.hpp"

#include <string>

namespace sw::game::properties
{
	enum class MovementType
	{
		All
	};

	struct Strength
	{
		unsigned int value;
	};

	struct Agility
	{
		unsigned int value;
	};

	struct Range
	{
		unsigned int value;
	};

	struct Movement
	{
		MovementType value;
	};

}
