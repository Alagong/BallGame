//
//	Manages the creation of components and binds a name to them so that we can do
//	object->AddComponent("ComponentName");
//

#pragma once
#include <map>
#include <string>
class Entity;
class Component;
class ComponentFactory
{
public:
	static ComponentFactory* Instance();

	ComponentFactory();
	virtual ~ComponentFactory();

	typedef Component* (* ComponentCreator) (Entity* entity, const std::string &name);

	void RegisterComponent(const std::string &name, ComponentCreator functor);
	Component* CreateComponent(Entity* entity, const std::string &name);
private:
	static std::map<std::string, ComponentCreator>* creators;
	static ComponentFactory* componentFactoryInstance;
};