#pragma once

#include <vector>

namespace sf
{
	class RenderWindow;
}

class CommandQueue;
class PlayState;
class Component;
class ComponentFactory;
class ComponentContainer
{
public:
	ComponentContainer(ComponentFactory& factory);
	virtual ~ComponentContainer();

	bool HasComponent(std::string name);
	Component* GetComponent(std::string name);
	Component* AddComponent(std::string name);
	bool RemoveComponent(std::string name);

	std::vector<std::string> GetComponentNames();

	void InitComponents();
	void UpdateComponents(float deltaTime);
	void DrawComponents(sf::RenderWindow* window);
	void ExecuteCommand(int command,int delay = 0, void* data = 0);
	void ExecuteEvent(int event, void* data = 0);
	ComponentFactory& factory;
private:
	CommandQueue* commandQueue;
	std::vector<Component*> components;
};