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
	COMMAND_JUMP,

	COMMAND_ACTION1,
	COMMAND_ACTION2,
	COMMAND_ACTION3,
	COMMAND_ACTION4

};

struct CommandData_Move
{
	bool start; //Start or stop moving
	int direction;
};
