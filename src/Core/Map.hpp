#pragma once

#include "Core/Position.hpp"

#include <memory>
#include <vector>

namespace sw::game
{
	class IUnit;

	class Map
	{
	public:
		Map(int width, int height);

		bool isValidPosition(Position pos) const;
		bool isCellOccupied(Position pos) const;
		bool moveUnit(std::shared_ptr<IUnit> unit, Position toPos);
		bool addUnit(std::shared_ptr<IUnit> unit);
		bool removeUnit(std::shared_ptr<IUnit> unit);
		std::vector<std::shared_ptr<IUnit>> getUnitAt(Position pos) const;
		std::vector<std::shared_ptr<IUnit>> getUnitsInRange(Position pos, int minRange, int maxRange) const;
		const std::vector<std::pair<unsigned int, std::shared_ptr<IUnit>>>& getUnits() const;
		void removeDeadUnits();
		void printMap() const;

	private:
		int width_;
		int height_;
		std::vector<std::vector<std::shared_ptr<IUnit>>> grid_;
		std::vector<std::pair<unsigned int, std::shared_ptr<IUnit>>> units_;
	};
}
