#include "Components/ButtonPressure.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include <Box2D\Box2D.h>
#include "defines.h"
#include "ObjectManager.h"
ButtonPressure::ButtonPressure(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posY = go->AddProperty<float>("PosY",0.0f);
	posX = go->AddProperty<float>("PosX",0.0f);
	height = go->AddProperty<float>("Height",0.0f);
	physBody = go->AddProperty<b2Body**>("PhysBody", &body);
	objectToActivate = go->AddProperty<int>("ObjectToActivate", 0);
	gravityScale = go->AddProperty<float>("GravityScale", -1.0f);
}

ButtonPressure::~ButtonPressure()
{

}

void ButtonPressure::Init()
{
	body = *physBody.Get();

	activated = false;

	maxHeightPos = posY.Get();
	activatePos = maxHeightPos + height/2;

	lockedPosX = posX.Get()/PTM_RATIO;

	maxHeightPos /= PTM_RATIO;
	activatePos /= PTM_RATIO;

	body->SetGravityScale( gravityScale.Get() );
	body->SetFixedRotation( true );
}

void ButtonPressure::Update(float delta)
{
	if( body->GetPosition().y < maxHeightPos )
	{
		body->SetTransform( b2Vec2( lockedPosX, maxHeightPos ), body->GetAngle() );
		body->SetLinearVelocity( b2Vec2( 0, 0 ) );
	} else if( body->GetPosition().y > activatePos )
	{
		if( !activated )
		{
			activated = true;
			body->SetAwake( false );
			Object* obj = ObjectManager::Instance()->GetObjectByID( objectToActivate );
			if( obj != NULL) 
				obj->GetProperty<bool>("Activated") = true;

			std::cout << "activated" << std::endl;
		}
	}
	body->SetTransform( b2Vec2( lockedPosX, body->GetPosition().y ), body->GetAngle() );
	if( activated )
	{
		body->SetTransform( b2Vec2( lockedPosX, activatePos ), body->GetAngle() );
		body->SetLinearVelocity( b2Vec2( 0, 0 ) );
	}
}

void ButtonPressure::Draw(sf::RenderWindow &window)
{

}

void ButtonPressure::ExecuteCommand(int command, void* data)
{

}

void ButtonPressure::ExecuteEvent(int event, void* data)
{

}