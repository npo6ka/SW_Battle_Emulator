#include "Features/Units/Swordsman.hpp"

#include "Features/Behaviors.hpp"
#include "Features/Properties.hpp"

namespace sw::game
{

	Swordsman::Swordsman(unsigned int id, int hp, unsigned int strength, const Position& pos) :
			Unit(id, hp, pos)
	{
		stats_.set(properties::Strength{strength});
		stats_.set(properties::Movement{properties::MovementType::All});

		auto& attackController = getAttackController();
		attackController.addBehavior(std::make_shared<MeleeAttackBehavior>());

		auto& movementController = getMovementController();
		movementController.addBehavior(std::make_shared<MoveToNearestUnitBehavior>());
	}

}
