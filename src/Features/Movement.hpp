#pragma once

#include "Core/Position.hpp"
#include "Features/Properties.hpp"

#include <vector>

namespace sw::game
{
	class Movement
	{
	public:
		static std::vector<Position> getMoves(const Position& current, properties::MovementType type)
		{
			std::vector<Position> moves;

			auto addStraightMoves = [&moves, &current]()
			{
				moves.push_back(Position(current.x + 1, current.y));
				moves.push_back(Position(current.x - 1, current.y));
				moves.push_back(Position(current.x, current.y + 1));
				moves.push_back(Position(current.x, current.y - 1));
			};

			auto addDiagonalMoves = [&moves, &current]()
			{
				moves.push_back(Position(current.x + 1, current.y + 1));
				moves.push_back(Position(current.x + 1, current.y - 1));
				moves.push_back(Position(current.x - 1, current.y + 1));
				moves.push_back(Position(current.x - 1, current.y - 1));
			};

			switch (type)
			{
				case properties::MovementType::All:
					// Все 8 направлений
					addStraightMoves();
					addDiagonalMoves();
					break;
			}

			return moves;
		}
	};
}
