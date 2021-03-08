#include "Components/BubbleAbsorbing.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include <iostream>
#include <Box2D/Box2D.h>
BubbleAbsorbing::BubbleAbsorbing(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	spriteRadius = go->AddProperty<float>("Width",0);
}

BubbleAbsorbing::~BubbleAbsorbing()
{

}

void BubbleAbsorbing::Init()
{
	absorbing = false;
}

void BubbleAbsorbing::Update(float delta)
{
	if( absorbing ) 
	{
		coreBubblePtr->GetProperty<float>("Width") += spriteRadius.Get();
		coreBubblePtr->GetProperty<float>("Height") += spriteRadius.Get();

		go->FlagForRemoval();
	}
}

void BubbleAbsorbing::Draw(sf::RenderWindow &window)
{

}

void BubbleAbsorbing::ExecuteCommand(int command, void* data)
{

}

void BubbleAbsorbing::ExecuteEvent(int event, void* data)
{
	if( event == EVENT_STARTEDCOLLIDING )
	{
		b2Contact *contact = (b2Contact*)data;
		Object* collidedWith;
		if( contact->GetFixtureA()->GetUserData() == go )
		{
			collidedWith = (Object*)contact->GetFixtureB()->GetUserData();
		} else
		{
			collidedWith = (Object*)contact->GetFixtureA()->GetUserData();
		}

		if( collidedWith->HasComponent("BallCoreController") )
		{
			absorbing = true;
			coreBubblePtr = collidedWith;
		}
	} 
}