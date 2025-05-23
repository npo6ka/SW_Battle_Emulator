#include "Features/Units/Hunter.hpp"

#include "Features/Behaviors.hpp"
#include "Features/Properties.hpp"

namespace sw::game
{

	Hunter::Hunter(
		unsigned int id, int hp, const Position& pos, unsigned int agility, unsigned int strength, unsigned int range) :
			Unit(id, hp, pos)
	{
		stats_.set(properties::Agility{agility});
		stats_.set(properties::Strength{strength});
		stats_.set(properties::Range{range});

		auto& behaviors = getBehaviors();
		behaviors.addBehavior(std::make_shared<MeleeAttackBehavior>());
		behaviors.addBehavior(std::make_shared<RangedAttackBehavior>());
		behaviors.addBehavior(std::make_shared<MoveToNearestUnitBehavior>());
	}

}
