#include "Core/Game.hpp"

#include "Features/Behaviors.hpp"

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

	void Game::addUnits(std::vector<std::shared_ptr<Unit>> units)
	{
		for (const auto& unit : units)
		{
			map_->addUnit(unit);
		}
	}

	void Game::removeUnits(std::vector<std::shared_ptr<Unit>> units)
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
			auto unit = unitIt->second;
			auto& behaviors = unit->getBehaviors();
			// вставляем предпоследним, чтобы атака была в приоритете
			behaviors.addBehavior(
				std::make_shared<MarchToTargetBehavior>(Position(x, y)), behaviors.getBehaviorCount() - 1);
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
