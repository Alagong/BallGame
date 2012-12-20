#pragma once
#include "ComponentEngine/ComponentContainer.h"
#include "ComponentEngine/PropertyContainer.h"
#include "ComponentEngine/ComponentFactory.h"
#include <iostream>
class Entity : public ComponentContainer, public PropertyContainer
{
public:
	Entity(ComponentFactory &factory) : ComponentContainer(factory), PropertyContainer()
	{
	}
	virtual ~Entity() {};
};