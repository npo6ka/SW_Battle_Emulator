#include "Core/Unit/IUnit.hpp"

#include "Core/Game.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::game
{

	IUnit::IUnit(unsigned int id, int hp, Position pos) :
			id_(id),
			hp_(hp),
			position_(pos)
	{}

	void IUnit::setHp(int hp)
	{
		hp_ = hp;
		if (hp_ <= 0)
		{
			hp_ = 0;
			eventLog.log(Game::getCurrentTurn(), io::UnitDied{this->getId()});
		}
	}

	void IUnit::attack(std::shared_ptr<IUnit> attacker, int damage)
	{
		eventLog.log(
			Game::getCurrentTurn(), io::UnitAttacked{attacker->getId(), this->getId(), damage, this->getHp() - damage});
		setHp(getHp() - damage);
	}

	void IUnit::setPosition(const Position& pos)
	{
		position_ = pos;
		eventLog.log(Game::getCurrentTurn(), io::UnitMoved{this->getId(), pos.x, pos.y});
	}

	void IUnit::act(std::shared_ptr<Map> map)
	{
		if (!attackController_.execute(shared_from_this(), map))
		{
			movementController_.execute(shared_from_this(), map);
		}
	}

}
