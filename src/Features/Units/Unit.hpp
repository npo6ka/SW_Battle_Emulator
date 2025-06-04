#pragma once

#include "Core/Unit/IUnit.hpp"
#include "Features/Behaviors.hpp"

namespace sw::game
{
	class Unit : public IUnit
	{
	public:
		Unit() = default;
		Unit(unsigned int id, int hp, Position pos): IUnit(id, hp, pos) {};
		virtual ~Unit() = default;

		virtual std::string getType() const override = 0;
        virtual void marchUnit(int x, int y) override {
            auto& behaviors = this->getMovementController();
			behaviors.addBehavior(std::make_shared<MarchToTargetBehavior>(Position(x, y)), 0);
        }
	};

}