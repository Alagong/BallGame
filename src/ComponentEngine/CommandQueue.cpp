#include "ComponentEngine/CommandQueue.h"
#include "ComponentEngine/ComponentContainer.h"
CommandQueue::CommandQueue(ComponentContainer * compContainer) : m_compContainer(compContainer)
{

}

void CommandQueue::AddCommand(int command, int delay, void* data)
{
	commands.push_back(new Command(command,delay,data));
}

void CommandQueue::Update()
{
	for(std::vector<Command*>::iterator it = commands.begin(); it != commands.end();)
	{
		if( (*it)->delay <= 0)
		{
			m_compContainer->ExecuteCommand( (*it)->command, 0, (*it)->data);
			delete (*it);
			it = commands.erase( it );
		} else {
			(*it)->delay--;
			++it;
		}
	}
}