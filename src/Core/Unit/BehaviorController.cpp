#include "Core/Unit/BehaviorController.hpp"

#include "Core/Map.hpp"
#include "Core/Unit/Behavior.hpp"
#include "Core/Unit/IUnit.hpp"

namespace sw::game
{
	void BehaviorController::addBehavior(std::shared_ptr<Behavior> behavior)
	{
		behaviors_.push_back(behavior);
	}

	void BehaviorController::addBehavior(std::shared_ptr<Behavior> behavior, int position)
	{
		if (position < 0 || position > behaviors_.size())
		{
			throw std::out_of_range("Invalid position for adding behavior");
		}
		behaviors_.insert(behaviors_.begin() + position, behavior);
	}

	void BehaviorController::removeBehavior(int position)
	{
		if (position < 0 || position >= behaviors_.size())
		{
			throw std::out_of_range("Invalid position for removing behavior");
		}
		behaviors_.erase(behaviors_.begin() + position);
	}

	void BehaviorController::addToFrontBehavior(std::shared_ptr<Behavior> behavior)
	{
		behaviors_.insert(behaviors_.begin(), behavior);
	}

	bool BehaviorController::execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map)
	{
		bool isCompleted = false;
		auto behavior = behaviors_.begin();	 // выполняем поведения пока это поведение не вернет успех
		while (behavior != behaviors_.end() && !isCompleted)
		{
			isCompleted = (*behavior)->execute(unit, map);
			++behavior;
		}
		removeFinishedBehaviors();

		return isCompleted;
	}

	void BehaviorController::removeFinishedBehaviors()
	{
		behaviors_.erase(
			std::remove_if(
				behaviors_.begin(), behaviors_.end(), [](const auto& behavior) { return behavior->isFinished(); }),
			behaviors_.end());
	}

	void BehaviorController::clearBehaviors()
	{
		behaviors_.clear();
	}

	size_t BehaviorController::getBehaviorCount() const
	{
		return behaviors_.size();
	}
}
