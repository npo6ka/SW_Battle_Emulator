#pragma once

#include <memory>

namespace sw::game
{
	class Map;
	class IUnit;

	class Behavior
	{
	public:
		virtual ~Behavior() = default;
		virtual bool execute(std::shared_ptr<IUnit> unit, std::shared_ptr<Map> map) = 0;

		bool isFinished() const
		{
			return isFinished_;
		}

	protected:
		void setFinished()
		{
			isFinished_ = true;
		}

	private:
		bool isFinished_ = false;
	};

}
