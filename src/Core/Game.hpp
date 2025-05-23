#pragma once

#include "Core/Map.hpp"
#include "Core/Unit/Unit.hpp"

#include <memory>
#include <vector>

namespace sw::game
{

	class Game
	{
	public:
		Game(){};

		void createMap(int width, int height);
		void addUnits(std::vector<std::shared_ptr<Unit>> units);
		void removeUnits(std::vector<std::shared_ptr<Unit>> units);
		void marchUnit(unsigned int unitId, int x, int y);
		void simulate();

		static unsigned int getCurrentTurn()
		{
			return currentTurn_;
		}

		bool isGameOver() const;

		std::shared_ptr<Map> getMap() const
		{
			return map_;
		}

	private:
		std::shared_ptr<Map> map_;
		inline static unsigned int currentTurn_ = 1;
	};

}
