#pragma once
#include "ComponentEngine/Entity.h"
#include <string>
class Object : public Entity
{
private:

	bool bFlaggedForRemoval;
	std::string name;

public:
	Object( ComponentFactory& factory ) : Entity(factory)
	{

	}

	bool ShouldBeRemoved() {return bFlaggedForRemoval;}
	void SetName( std::string& name ) { this->name = name; }
};