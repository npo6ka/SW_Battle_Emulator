#include <Core/Game.hpp>
#include <Core/Position.hpp>
#include <Core/Unit/Unit.hpp>
#include <Features/Units/Hunter.hpp>
#include <Features/Units/Swordsman.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	game::Game SWGame;

	io::CommandParser parser;
	parser.add<io::CreateMap>([&SWGame](auto command) { SWGame.createMap(command.width, command.height); })
		.add<io::SpawnSwordsman>(
			[&SWGame](auto command)
			{
				SWGame.addUnits({std::make_shared<game::Swordsman>(
					command.unitId, command.hp, command.strength, game::Position(command.x, command.y))});
			})
		.add<io::SpawnHunter>(
			[&SWGame](auto command)
			{
				SWGame.addUnits({std::make_shared<game::Hunter>(
					command.unitId,
					command.hp,
					game::Position(command.x, command.y),
					command.agility,
					command.strength,
					command.range)});
			})
		.add<io::March>([&SWGame](auto command)
						{ SWGame.marchUnit(command.unitId, command.targetX, command.targetY); });

	std::cout << "\n\nEvents:\n";

	parser.parse(file);

	while (!SWGame.isGameOver())
	{
		SWGame.simulate();
	}

	return 0;
}
