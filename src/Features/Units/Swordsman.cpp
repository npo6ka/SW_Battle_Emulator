#include "Features/Units/Swordsman.hpp"

#include "Features/Behaviors.hpp"
#include "Features/Properties.hpp"

namespace sw::game
{

	Swordsman::Swordsman(unsigned int id, int hp, unsigned int strength, const Position& pos) :
			Unit(id, hp, pos)
	{
		stats_.set(properties::Strength{strength});

		auto& behaviors = getBehaviors();
		behaviors.addBehavior(std::make_shared<MeleeAttackBehavior>());
		behaviors.addBehavior(std::make_shared<MoveToNearestUnitBehavior>());
	}

}
