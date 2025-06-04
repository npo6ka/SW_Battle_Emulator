#include "Core/Game.hpp"

#include <IO/Events/MarchStarted.hpp>
#include <IO/System/EventLog.hpp>
#include <algorithm>
#include <vector>

namespace sw::game
{
	void Game::createMap(int width, int height)
	{
		map_ = std::make_shared<Map>(width, height);
	}

	void Game::addUnits(std::vector<std::shared_ptr<IUnit>> units)
	{
		for (const auto& unit : units)
		{
			map_->addUnit(unit);
		}
	}

	void Game::removeUnits(std::vector<std::shared_ptr<IUnit>> units)
	{
		for (const auto& unit : units)
		{
			map_->removeUnit(unit);
		}
	}

	void Game::marchUnit(unsigned int unitId, int x, int y)
	{
		auto unitIt = std::find_if(
			map_->getUnits().begin(),
			map_->getUnits().end(),
			[unitId](const auto& pair) { return pair.first == unitId; });
		if (unitIt != map_->getUnits().end())
		{
			std::shared_ptr<IUnit> unit = unitIt->second;
			unit->marchUnit(x, y);
			eventLog.log(currentTurn_, io::MarchStarted{unitId, unit->getPosition().x, unit->getPosition().y, x, y});
		}
	}

	void Game::simulate()
	{
		currentTurn_++;

		for (const auto& [id, unit] : map_->getUnits())
		{
			if (unit->isAlive())
			{
				unit->act(map_);
			}
		}

		map_->removeDeadUnits();
	}

	bool Game::isGameOver() const
	{
		int aliveUnits = 0;
		for (const auto& [id, unit] : map_->getUnits())
		{
			if (unit->isAlive())
			{
				aliveUnits++;
			}
		}
		return aliveUnits <= 1;
	}

}
