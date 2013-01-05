#pragma once
#include "ComponentEngine/Entity.h"
#include <string>
class Object : public Entity
{
private:

	bool bFlaggedForRemoval;
	std::string name;
	int id;

public:
	Object( ComponentFactory& factory ) : Entity(factory)
	{
		bFlaggedForRemoval = false;
	}

	void FlagForRemoval() {bFlaggedForRemoval = true;}
	bool ShouldBeRemoved() {return bFlaggedForRemoval;}
	void SetName( std::string& name ) { this->name = name; }

	int GetID() { return id;}
	void SetID(int id) {this->id = id;}
};