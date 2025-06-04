#pragma once

#include "Core/Map.hpp"
#include "Core/Unit/Behavior.hpp"
#include "Core/Unit/IUnit.hpp"
#include "Features/Movement.hpp"
#include "Features/Properties.hpp"

#include <queue>
#include <unordered_set>

namespace sw::game
{
	class MoveBehavior : public Behavior
	{
	public:
		virtual bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override = 0;

		std::vector<Position> getPath(
			Position start, Position target, std::shared_ptr<Map> map, properties::MovementType movementType)
		{
			std::vector<Position> path = {};
			std::queue<Position> queue;
			std::unordered_set<Position> visited;
			std::unordered_map<Position, Position> parents;

			queue.push(start);
			visited.insert(start);
			parents[start] = start;
			Position current = start;

			while (!queue.empty() && current != target)
			{
				current = queue.front();
				queue.pop();

				for (const auto& neighbor : Movement::getMoves(current, movementType))
				{
					if (map->isValidPosition(neighbor) && visited.count(neighbor) == 0
						&& (!map->isCellOccupied(neighbor) || neighbor == target))
					{
						queue.push(neighbor);
						visited.insert(neighbor);
						if (parents.count(neighbor) == 0)
						{
							parents[neighbor] = current;
						}
					}
				}
			}

			if (parents.count(target) != 0)
			{
				while (target != start)
				{
					path.push_back(target);
					target = parents[target];
				}
			}
			std::reverse(path.begin(), path.end());

			return path;
		}
	};

	class MarchToTargetBehavior : public MoveBehavior
	{
	public:
		MarchToTargetBehavior(Position target) :
				target_(target)
		{}

		bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override
		{
			Position start = unit->getPosition();
			if (start == target_)
			{
				setFinished();
				return false;
			}

			auto path = getPath(start, target_, map, unit->getStats().get<properties::Movement>().value);
			if (path.empty())
			{
				return false;
			}

			map->moveUnit(unit, path.front());

			return true;
		}

	private:
		Position target_;
	};

	class MoveToNearestUnitBehavior : public MoveBehavior
	{
	public:
		bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override
		{
			Position pos = unit->getPosition();
			auto units = map->getUnits();
			std::shared_ptr<IUnit> targetUnit;
			int distanceToTarget = INT_MAX;

			for (const auto& [opponentId, opponent] : units)
			{
				if (opponent != unit && opponent->isAlive() && opponent->getDistance(*unit) < distanceToTarget)
				{
					distanceToTarget = opponent->getDistance(*unit);
					targetUnit = opponent;
				}
			}

			if (targetUnit)
			{
				auto path
					= getPath(pos, targetUnit->getPosition(), map, unit->getStats().get<properties::Movement>().value);
				if (!path.empty())
				{
					map->moveUnit(unit, path.front());
				}
			}

			return true;
		}

	private:
		Position target_;
	};

	class DamageBehavior : public Behavior
	{
	public:
		virtual bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override = 0;

		bool dealDamage(std::shared_ptr<IUnit> unit, std::vector<std::shared_ptr<IUnit>> unitsInRange, int damage)
		{
			if (!unitsInRange.empty())
			{
				while (!unitsInRange.empty())
				{  // ищем юнита которого можем проатаковать
					auto opponent = unitsInRange.back();
					int distance = opponent->getDistance(*unit);
					if (opponent->canBeAttacked(damage, distance))
					{
						opponent->attack(unit, damage);
						return true;
					}
					else
					{
						unitsInRange.pop_back();
					}
				}
			}
			return false;
		}
	};

	class MeleeAttackBehavior : public DamageBehavior
	{
	public:
		bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override
		{
			const Position& pos = unit->getPosition();
			properties::Strength strength = unit->getStats().get<properties::Strength>();
			auto adjacentUnits = map->getUnitsInRange(*unit, 1, 1);

			return dealDamage(unit, adjacentUnits, strength.value);
		}
	};

	class RangedAttackBehavior : public DamageBehavior
	{
	public:
		bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) override
		{
			const Position& pos = unit->getPosition();
			properties::Agility agility = unit->getStats().get<properties::Agility>();
			properties::Range range = unit->getStats().get<properties::Range>();

			auto unitsInRange = map->getUnitsInRange(*unit, 2, range.value + 1);

			return dealDamage(unit, unitsInRange, agility.value);
		}
	};

}
