#pragma once

#include <cstdint>

namespace sw::io
{
	struct MarchStarted
	{
		constexpr static const char* Name = "MARCH_STARTED";

		uint32_t unitId{};
		int32_t x{};
		int32_t y{};
		int32_t targetX{};
		int32_t targetY{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}
