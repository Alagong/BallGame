#pragma once

enum CompCommands
{
	COMMAND_DIE,
	COMMAND_REMOVE,
	COMMAND_TAKEDAMAGE,
	COMMAND_TAKEPARENTEDDAMAGE,
	COMMAND_CONVERTDAMAGE, // other components can have protection against types of damage, we need them to convert it to pure
	COMMAND_TAKEBLAST, //Take blast from explosion
	COMMAND_SPAWNOBJECT,

	//Movement input
	COMMAND_MOVE,
	COMMAND_JUMP

};

struct CommandData_Move
{
	bool start; //Start or stop moving
	int direction;
};
