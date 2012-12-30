#include "Components/BodyStatic.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include "PhysicsManager.h"
#include <Box2D\Box2D.h>
BodyStatic::BodyStatic(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body = NULL;

	spriteWidth = go->AddProperty<float>("SpriteWidth",32.0f);
	spriteHeight = go->AddProperty<float>("SpriteHeight",32.0f);

	posX = go->AddProperty<float>("PosX",0.0f);
	posY = go->AddProperty<float>("PosY",0.0f);

	rotation = go->AddProperty<float>("Rotation",0.0f);

	physBody = go->AddProperty<b2Body**>("PhysBody", &body);
	staticObject = go->AddProperty<bool>("StaticObject",false);
}

BodyStatic::~BodyStatic()
{
	if(body)
		PhysicsManager::Instance()->DestroyBody( body );
	physBody.Set(NULL);
}

void BodyStatic::Init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( posX.Get()/PTM_RATIO, posY.Get()/PTM_RATIO );
	bodyDef.angle = rotation*DEGTORAD;
	body = PhysicsManager::Instance()->CreateBody( &bodyDef );

	body->SetUserData( go );
	staticObject.Set(true);
}

void BodyStatic::Update(float delta)
{

}

void BodyStatic::Draw(sf::RenderWindow &window)
{

}

void BodyStatic::ExecuteCommand(int command, void* data)
{

}

void BodyStatic::ExecuteEvent(int event, void* data)
{

}