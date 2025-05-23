#include "Core/Unit/Unit.hpp"

#include "Core/Game.hpp"
#include "Features/Properties.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/System/EventLog.hpp"

namespace sw::game
{

	Unit::Unit(unsigned int id, int hp, Position pos) :
			id_(id),
			hp_(hp),
			position_(pos)
	{
		stats_.set(properties::Movement{properties::MovementType::All});
	}

	void Unit::setHp(int hp)
	{
		hp_ = hp;
		if (hp_ <= 0)
		{
			hp_ = 0;
			eventLog.log(Game::getCurrentTurn(), io::UnitDied{this->getId()});
		}
	}

	void Unit::attack(std::shared_ptr<Unit> attacker, int damage)
	{
		eventLog.log(
			Game::getCurrentTurn(), io::UnitAttacked{attacker->getId(), this->getId(), damage, this->getHp() - damage});
		setHp(getHp() - damage);
	}

	void Unit::setPosition(const Position& pos)
	{
		position_ = pos;
		eventLog.log(Game::getCurrentTurn(), io::UnitMoved{this->getId(), pos.x, pos.y});
	}

	void Unit::act(std::shared_ptr<Map> map)
	{
		behaviorController_.execute(shared_from_this(), map);
	}

}
