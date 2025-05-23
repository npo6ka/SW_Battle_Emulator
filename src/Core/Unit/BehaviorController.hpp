#pragma once

#include <memory>
#include <vector>

namespace sw::game
{
	class Behavior;
	class Unit;
	class Map;

	class BehaviorController
	{
	public:
		BehaviorController() = default;
		~BehaviorController() = default;

		void addBehavior(std::shared_ptr<Behavior> behavior);
		void addBehavior(std::shared_ptr<Behavior> behavior, int position);
		void removeBehavior(int position);
		void addToFrontBehavior(std::shared_ptr<Behavior> behavior);
		void execute(std::shared_ptr<Unit> unit, std::shared_ptr<Map> map);
		void removeFinishedBehaviors();
		void clearBehaviors();
		size_t getBehaviorCount() const;

	private:
		std::vector<std::shared_ptr<Behavior>> behaviors_;
	};
}
