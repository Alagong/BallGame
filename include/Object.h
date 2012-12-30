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
		bFlaggedForRemoval = false;
	}

	void FlagForRemoval() {bFlaggedForRemoval = true;}
	bool ShouldBeRemoved() {return bFlaggedForRemoval;}
	void SetName( std::string& name ) { this->name = name; }
};