#include "Components/CornerPosition.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
CornerPosition::CornerPosition(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posX = go->AddProperty<float>("PosX",0);
	posY = go->AddProperty<float>("PosY",0);

	cposX = go->AddProperty<float>("CPosX",0);
	cposY = go->AddProperty<float>("CPosY",0);

	width = go->AddProperty<float>("Width",0);
	height = go->AddProperty<float>("Height",0);
}

CornerPosition::~CornerPosition()
{

}

void CornerPosition::Init()
{
	posX = cposX + width/2;
	posY = cposY + height/2;
}

void CornerPosition::Update(float delta)
{

}

void CornerPosition::Draw(sf::RenderWindow &window)
{

}

void CornerPosition::ExecuteCommand(int command, void* data)
{

}

void CornerPosition::ExecuteEvent(int event, void* data)
{
	 
};