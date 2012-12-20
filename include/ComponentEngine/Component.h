#pragma once
#include "ComponentEngine/Property.h"
#include <string>

namespace sf
{
	class RenderWindow;
}
class Entity;
class Component
{
public:
	Component(Entity* entity, const std::string &name) : entity(entity), name(name) {};
	virtual ~Component() {};
	virtual std::string GetName() { return name; }

	virtual void Init() {};
	virtual void Update(float delta) {};
	virtual void Draw(sf::RenderWindow* window) {};

	virtual void ExecuteCommand(int command, void* data = 0) {};
	virtual void ExecuteEvent(int event, void* data) {};
protected:
	Entity* entity;
	std::string name;
};