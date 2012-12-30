#include "Components/BallCoreController.h"
#include <boost/bind.hpp>
#include "Object.h"
#include <Box2D\Box2D.h>
#include "ComponentEngine\CompEvents.h"
#include "ComponentEngine\CompCommands.h"
#include "PhysicsManager.h"
#include "QueryCallbacks.h"
#include "defines.h"
#include <iostream>
BallCoreController::BallCoreController(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body           = NULL;
	posX           = go->AddProperty<float>("PosX",0);
	posY           = go->AddProperty<float>("PosY",0);
	spriteRadius	= go->AddProperty<float>("Width",0);
	physBody       = go->AddProperty<b2Body**>("PhysBody", &body);
	height			= go->AddProperty<float>("Height",0);
}

BallCoreController::~BallCoreController()
{

}

void BallCoreController::Init()
{
	body = *physBody.Get();

	for( int i = 0; i < 4; ++i )
	{
		movingDirection[i] = false;
	}
}

void BallCoreController::Update(float delta)
{
	if( movingDirection[0] )
	{
		body->ApplyForceToCenter( b2Vec2( 3.0, 0 ) );
	}
	if( movingDirection[2] )
	{
		body->ApplyForceToCenter( b2Vec2( -3.0, 0 ) );
	}

	if( movingDirection[3] )
	{
		QueryObjectsAABB callback;
		b2AABB aabb;
		aabb.lowerBound = b2Vec2( ( posX.Get() - spriteRadius/2 )/PTM_RATIO, ( posY.Get() - spriteRadius/2 )/PTM_RATIO );
		aabb.upperBound = b2Vec2( ( posX.Get() + spriteRadius/2 )/PTM_RATIO, ( posY.Get() + spriteRadius/2 )/PTM_RATIO );
		PhysicsManager::Instance()->GetWorld()->QueryAABB( &callback, aabb );

		std::vector<b2Fixture*> &fixtures = callback.fixtures;

		for(std::vector<b2Fixture*>::iterator it = fixtures.begin(); it != fixtures.end(); ++it )
		{
			Object* obj = (Object*)(*it)->GetUserData();
			if( obj == go ) continue;

			if( obj->HasComponent( "BubbleAbsorbable" ) )
			{
				std::cout << "yes" << std::endl;
				spriteRadius += obj->GetProperty<float>("Width");
				height = spriteRadius.Get();
				obj->FlagForRemoval();
			}
		}
	}
}

void BallCoreController::Draw(sf::RenderWindow &window)
{

}

void BallCoreController::ExecuteCommand(int command, void* data)
{
	switch( command )
	{
	case COMMAND_JUMP:
		{
			body->SetLinearVelocity( b2Vec2( body->GetLinearVelocity().x, -5 ) );
			break;
		}
	case COMMAND_MOVE:
		{
			CommandData_Move* moveData = (CommandData_Move*)data;
			if( moveData->start )
			{
				movingDirection[ moveData->direction ] = true;
			} else {
				movingDirection[ moveData->direction ] = false;
			}
			break;
		}
	default:
		break;
	}
}

void BallCoreController::ExecuteEvent(int event, void* data)
{
	if( event == EVENT_STARTEDCOLLIDING )
	{
		Object* collidedWith = (Object*)data;
	}
}