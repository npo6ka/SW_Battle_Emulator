#pragma once

#include "Core/Position.hpp"

#include <memory>
#include <vector>

namespace sw::game
{
	class Unit;

	class Map
	{
	public:
		Map(int width, int height);

		bool isValidPosition(Position pos) const;
		bool isCellOccupied(Position pos) const;
		bool moveUnit(std::shared_ptr<Unit> unit, Position toPos);
		bool addUnit(std::shared_ptr<Unit> unit);
		bool removeUnit(std::shared_ptr<Unit> unit);
		std::vector<std::shared_ptr<Unit>> getUnitAt(Position pos) const;
		std::vector<std::shared_ptr<Unit>> getUnitsInRange(Position pos, int minRange, int maxRange) const;
		const std::vector<std::pair<unsigned int, std::shared_ptr<Unit>>>& getUnits() const;
		void removeDeadUnits();
		void printMap() const;

	private:
		int width_;
		int height_;
		std::vector<std::vector<std::shared_ptr<Unit>>> grid_;
		std::vector<std::pair<unsigned int, std::shared_ptr<Unit>>> units_;
	};
}
