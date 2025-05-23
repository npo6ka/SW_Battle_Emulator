#pragma once

#include <cstdint>
#include <string>

namespace sw::io
{
	struct UnitAttacked
	{
		constexpr static const char* Name = "UNIT_ATTACKED";

		uint32_t attackerUnitId{};
		uint32_t targetUnitId{};
		int32_t damage{};
		int32_t targetHp{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("attackerUnitId", attackerUnitId);
			visitor.visit("targetUnitId", targetUnitId);
			visitor.visit("damage", damage);
			visitor.visit("targetHp", targetHp);
		}
	};
}
