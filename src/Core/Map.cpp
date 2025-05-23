#include "Core/Map.hpp"

#include "Core/Game.hpp"
#include "Core/Unit/Unit.hpp"

#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/EventLog.hpp>
#include <cmath>
#include <iomanip>

namespace sw::game
{

	Map::Map(int width, int height) :
			width_(width),
			height_(height)
	{
		grid_.resize(height, std::vector<std::shared_ptr<Unit>>(width));
		eventLog.log(Game::getCurrentTurn(), io::MapCreated{width, height});
	}

	bool Map::isValidPosition(Position pos) const
	{
		return pos.x >= 0 && pos.x < width_ && pos.y >= 0 && pos.y < height_;
	}

	bool Map::isCellOccupied(Position pos) const
	{
		return isValidPosition(pos) && grid_[pos.y][pos.x] != nullptr;
	}

	bool Map::moveUnit(std::shared_ptr<Unit> unit, Position toPos)
	{
		if (!isValidPosition(toPos) || (isCellOccupied(toPos) && unit->isTakesUpCell()))
		{
			return false;
		}

		auto fromPos = unit->getPosition();
		unit->setPosition(toPos);  // не факт что механика юнита позволит двигаться на заданную клетку
		if (fromPos == unit->getPosition())
		{  // если никуда не сдвинулись, то возвращаем false
			return false;
		}
		toPos = unit->getPosition();

		if (fromPos != toPos && unit->isTakesUpCell())
		{
			grid_[toPos.y][toPos.x] = unit;
			grid_[fromPos.y][fromPos.x] = nullptr;
		}

		return true;
	}

	bool Map::addUnit(std::shared_ptr<Unit> unit)
	{
		Position pos = unit->getPosition();

		if (!isValidPosition(pos) || (isCellOccupied(pos) && unit->isTakesUpCell()))
		{
			return false;
		}

		if (unit->isTakesUpCell())
		{
			grid_[pos.y][pos.x] = unit;
		}

		units_.push_back(std::make_pair(unit->getId(), unit));
		eventLog.log(Game::getCurrentTurn(), io::UnitSpawned{unit->getId(), unit->getType(), pos.x, pos.y});

		return true;
	}

	bool Map::removeUnit(std::shared_ptr<Unit> unit)
	{
		Position pos = unit->getPosition();

		if (grid_[pos.y][pos.x] && unit->isTakesUpCell())
		{
			grid_[pos.y][pos.x] = nullptr;
		}
		auto unitIt = std::find_if(
			units_.begin(), units_.end(), [unit](const auto& pair) { return pair.first == unit->getId(); });
		if (unitIt != units_.end())
		{
			units_.erase(unitIt);
			return true;
		}
		return false;
	}

	std::vector<std::shared_ptr<Unit>> Map::getUnitAt(Position pos) const
	{
		std::vector<std::shared_ptr<Unit>> units = {};
		if (!isValidPosition(pos))
		{
			return units;
		}

		for (const auto& [id, unit] : units_)
		{
			if (unit->getPosition() == pos)
			{
				units.push_back(unit);
			}
		}

		return units;
	}

	std::vector<std::shared_ptr<Unit>> Map::getUnitsInRange(Position pos, int minRange, int maxRange) const
	{
		std::vector<std::shared_ptr<Unit>> units;
		for (const auto& [id, unit] : units_)
		{
			if (unit->getDistance(pos) >= minRange && unit->getDistance(pos) <= maxRange)
			{
				units.push_back(unit);
			}
		}

		return units;
	}

	const std::vector<std::pair<unsigned int, std::shared_ptr<Unit>>>& Map::getUnits() const
	{
		return units_;
	}

	void Map::removeDeadUnits()
	{
		std::vector<std::shared_ptr<Unit>> deadUnits;
		for (const auto& [id, unit] : units_)
		{
			if (!unit->isAlive())
			{
				deadUnits.push_back(unit);
			}
		}
		for (const auto& unit : deadUnits)
		{
			removeUnit(unit);
		}
	}

	void Map::printMap() const
	{
		std::cout << "--------------------------------" << std::endl;
		for (int y = 0; y < height_; y++)
		{
			for (int x = 0; x < width_; x++)
			{
				if (grid_[y][x])
				{
					std::cout << std::setfill('0') << std::setw(2) << grid_[y][x]->getId() << " ";
				}
				else
				{
					std::cout << "   ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "--------------------------------" << std::endl;
	}
}
