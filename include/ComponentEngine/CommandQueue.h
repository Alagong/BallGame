//
//	A command queue class used to send commands to objects with a delay
//

#pragma once
#include <vector>
class ComponentContainer;
class Object;
struct Command
{
	int command;
	int delay;
	void* data;
	Command(int command, int delay, void *data)
	{
		this->command = command;
		this->delay = delay;
		this->data = data;
	}
};

class CommandQueue
{
public:
	CommandQueue(ComponentContainer* compContainer);

	void AddCommand(int command, int delay, void* data);
	void Update();
private:
	ComponentContainer* m_compContainer;
	std::vector<Command*> commands;
};