#include "Components/BubbleAbsorbable.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include "QueryCallbacks.h"
#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include "defines.h"
BubbleAbsorbable::BubbleAbsorbable(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posX = go->AddProperty<float>("PosX",0);
	posY = go->AddProperty<float>("PosY",0);
	spriteRadius = go->AddProperty<float>("SpriteWidth",0);
}

BubbleAbsorbable::~BubbleAbsorbable()
{
}

void BubbleAbsorbable::Init()
{
}

void BubbleAbsorbable::Update(float delta)
{
}

void BubbleAbsorbable::Draw(sf::RenderWindow &window)
{

}

void BubbleAbsorbable::ExecuteCommand(int command, void* data)
{

}

void BubbleAbsorbable::ExecuteEvent(int event, void* data)
{
	 
}