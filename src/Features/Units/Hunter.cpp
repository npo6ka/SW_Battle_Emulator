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
		stats_.set(properties::Movement{properties::MovementType::All});

		auto& movementController = getMovementController();
		movementController.addBehavior(std::make_shared<MoveToNearestUnitBehavior>());

		auto& attackController = getAttackController();
		attackController.addBehavior(std::make_shared<MeleeAttackBehavior>());
		attackController.addBehavior(std::make_shared<RangedAttackBehavior>());
	}

}
