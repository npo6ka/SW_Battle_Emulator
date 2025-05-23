#pragma once

#include <functional>

namespace sw::game
{

	struct Position
	{
		int x;
		int y;

		Position() :
				x(-1),
				y(-1)
		{}

		Position(int x, int y) :
				x(x),
				y(y)
		{}

		bool isValid() const
		{
			return x >= 0 && y >= 0;
		}

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Position& other) const
		{
			return !(*this == other);
		}

		Position operator+(const Position& other) const
		{
			return Position(x + other.x, y + other.y);
		}
	};

}

template <>
struct std::hash<sw::game::Position>
{
	size_t operator()(const sw::game::Position& pos) const
	{
		return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
	}
};
