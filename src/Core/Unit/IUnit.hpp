#pragma once

#include "Core/Position.hpp"
#include "Core/Unit/BehaviorController.hpp"
#include "Core/Unit/UnitStats.hpp"

#include <memory>
#include <string>

namespace sw::game
{

	class Map;
	class Behavior;

	class IUnit : public std::enable_shared_from_this<IUnit>
	{
	public:
		IUnit() = default;
		IUnit(unsigned int id, int hp, Position pos);
		virtual ~IUnit() = default;

		unsigned int getId() const
		{
			return id_;
		}

		int getHp() const
		{
			return hp_;
		}

		void setHp(int hp);
		virtual void attack(std::shared_ptr<IUnit> attacker, int damage);

		const Position& getPosition() const
		{
			return position_;
		}

		virtual void setPosition(const Position& pos);

		UnitStats& getStats()
		{
			return stats_;
		}

		const UnitStats& getStats() const
		{
			return stats_;
		}

		BehaviorController& getMovementController()
		{
			return movementController_;
		}

		BehaviorController& getAttackController()
		{
			return attackController_;
		}

		bool isAlive() const
		{
			return hp_ > 0;
		}

		void act(std::shared_ptr<Map> map);
		virtual std::string getType() const = 0;

		virtual bool canBeAttacked(int damage, int attackDistance) const
		{
			return true;
		}

		virtual int getDistance(Position pos) const
		{
			return std::max(std::abs(pos.x - position_.x), std::abs(pos.y - position_.y));
		}

		virtual bool isTakesUpCell() const
		{
			return true;
		}

		virtual void marchUnit(int x, int y) = 0;

	protected:
		unsigned int id_;
		int hp_;
		Position position_;
		BehaviorController movementController_;
		BehaviorController attackController_;
		UnitStats stats_;
	};

}
