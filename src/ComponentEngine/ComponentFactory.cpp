#include "ComponentEngine/ComponentFactory.h"
#include "ComponentEngine/Entity.h"
#include "ComponentEngine/Component.h"
std::map<std::string, ComponentFactory::ComponentCreator>* ComponentFactory::creators;
ComponentFactory* ComponentFactory::componentFactoryInstance;
ComponentFactory* ComponentFactory::Instance()
{
	if( !componentFactoryInstance )
		componentFactoryInstance = new ComponentFactory();
	return componentFactoryInstance;
}

ComponentFactory::ComponentFactory()
{
}

ComponentFactory::~ComponentFactory()
{
	if(creators)
	{
		creators->clear();
		delete creators;
	}
}

void ComponentFactory::RegisterComponent(const std::string& type, ComponentCreator functor)
{
	if(creators == 0)
		creators = new std::map<std::string, ComponentCreator>();

	if(creators->find(type) == creators->end())
	{
		std::pair<std::string, ComponentCreator> value(type, functor);
		creators->insert(value);
	}
}

Component* ComponentFactory::CreateComponent(Entity* entity, const std::string& name)
{
	if(creators == 0)
		return 0;

	std::map<std::string, ComponentCreator>::iterator creatorIt = creators->find(name);
	if(creatorIt == creators->end())
		throw "Unable to create component";
	
	ComponentCreator creator = creatorIt->second;

	return creator(entity, name);
}