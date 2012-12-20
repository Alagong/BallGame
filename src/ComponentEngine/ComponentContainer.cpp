#include "ComponentEngine/ComponentContainer.h"
#include "ComponentEngine/ComponentFactory.h"
#include "ComponentEngine/Entity.h"
#include "ComponentEngine/Component.h"
#include "ComponentEngine/CommandQueue.h"

#include <iostream>
ComponentContainer::ComponentContainer(ComponentFactory& factory) : factory(factory) 
{
	commandQueue = new CommandQueue(this);
}

ComponentContainer::~ComponentContainer()
{
	std::vector<Component*>::iterator it;
	for(it = components.begin(); it != components.end();)
	{
		if((*it))
		{
			delete (*it);
			it = components.erase( it );
		} else {
			++it;
		}
	}

	components.clear();
}

bool ComponentContainer::HasComponent(std::string name)
{
	std::vector<Component*>::iterator it;
	for(it = components.begin(); it != components.end(); ++it)
	{
		Component *component = (*it);
		if(component->GetName() == name)
			return true;
	}
	return false;
}

Component* ComponentContainer::GetComponent(std::string name)
{
	std::vector<Component*>::iterator it;
	for(it = components.begin(); it != components.end(); ++it)
	{
		Component *component = (*it);
		if(component->GetName() == name)
		{
			return component;
		}
	}
	throw "Component not found";
}

Component* ComponentContainer::AddComponent(std::string name)
{
	std::vector<Component*>::iterator it;
	for(it = components.begin(); it != components.end(); ++it)
	{
		Component *component = (*it);
		if(component->GetName() == name)
			return component;
	}

	Component* component = factory.CreateComponent(static_cast<Entity*>(this), name);
	if(component)
	{
		components.push_back(component);
		return component;
	}
	else
		throw "Unable to create component " + name;
}

bool ComponentContainer::RemoveComponent(std::string compName)
{
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		if(strcmp( (*it)->GetName().c_str(), compName.c_str() ) == 0 )
		{
			delete (*it);
			(*it) = NULL;
			it = components.erase( it );
			return true;
		}
	}
	return false;
}

std::vector<std::string> ComponentContainer::GetComponentNames()
{
	std::vector<std::string> names;

	std::vector<Component*>::iterator it;
	for(it = components.begin(); it != components.end(); ++it)
	{
		Component *component = (*it);
		std::string name = component->GetName();
		names.push_back(name);
	}
	return names;
}


void ComponentContainer::InitComponents()
{
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->Init();
	}
}

void ComponentContainer::UpdateComponents(float deltaTime)
{
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	commandQueue->Update();
}

void ComponentContainer::DrawComponents(sf::RenderWindow* window)
{
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->Draw(window);
	}
}

void ComponentContainer::ExecuteCommand(int event, int delay, void* data)
{
	if(delay <= 0)
	{
		for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
		{
			(*it)->ExecuteCommand(event,data);
		}
	} else {
		commandQueue->AddCommand(event,delay,data);
	}
}

void ComponentContainer::ExecuteEvent(int event, void* data)
{
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		(*it)->ExecuteEvent(event,data);
	}
}


