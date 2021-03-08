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
#include <math.h>

#include "ObjectTemplateManager.h"
#include "ObjectManager.h"

#include "Input.h"
BallCoreController::BallCoreController(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body           = NULL;
	posX           = go->AddProperty<float>("PosX",0);
	posY           = go->AddProperty<float>("PosY",0);
	spriteRadius	= go->AddProperty<float>("Width",0);
	physBody       = go->AddProperty<b2Body**>("PhysBody", &body);
	height			= go->AddProperty<float>("Height",0);
	cameraZoom	=	go->AddProperty<float>("CameraZoom", 1.0 );
}

BallCoreController::~BallCoreController()
{

}

void BallCoreController::Init()
{
	spriteRadius.ValueChanged().connect(boost::bind(&BallCoreController::OnWidthChanged,this,_1,_2));
	body = *physBody.Get();

	for( int i = 0; i < 4; ++i )
	{
		movingDirection[i] = false;
	}

	absorbed = false;

	cameraZoom = spriteRadius/70;

	jumping = false;

	split = false;
}

void BallCoreController::Update(float delta)
{
	float maxSpeed = spriteRadius.Get()/7;
	if ( abs( sf::Joystick::getAxisPosition(0,sf::Joystick::X) ) > 0.3 )
	{
		float speed = sf::Joystick::getAxisPosition(0,sf::Joystick::X)/100;
		if( abs(body->GetLinearVelocity().x) < abs(maxSpeed) )
		{
			body->ApplyForceToCenter( b2Vec2( maxSpeed * speed, 0 ) );
		}
	}

	if( Input::IsKeyDown( sf::Keyboard::Right ) )
	{
		if( body->GetLinearVelocity().x < maxSpeed )
		{
			if( body->GetLinearVelocity().x < 0 )
			{
				body->ApplyForceToCenter( b2Vec2( maxSpeed, 0 ) );
			} else 
			{
				body->ApplyForceToCenter( b2Vec2( maxSpeed, 0 ) );
			}
		}
	}
	if( Input::IsKeyDown( sf::Keyboard::Left ) )
	{
		if( body->GetLinearVelocity().x > -maxSpeed )
		{
			if( body->GetLinearVelocity().x > 0 )
			{
				body->ApplyForceToCenter( b2Vec2( -maxSpeed*2, 0 ) );
			} else 
			{
				body->ApplyForceToCenter( b2Vec2( -maxSpeed, 0 ) );
			}
		}
	}

	if( !Input::IsKeyDown( sf::Keyboard::Left ) && !Input::IsKeyDown( sf::Keyboard::Right ) )
	{
		body->SetLinearVelocity( b2Vec2(body->GetLinearVelocity().x/1.1, body->GetLinearVelocity().y ) );
	}

	if( absorbing )
	{
		if( !absorbed )
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
			absorbed = true;
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
			if( !jumping )
			{
				float vel = sqrt(sqrt( spriteRadius.Get()*2*9.81 ));//what
				body->SetLinearVelocity( b2Vec2( body->GetLinearVelocity().x, -vel ) );
				jumping = true;
			}
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
	case COMMAND_ACTION1:
		{
			if( (bool)data )
			{
				if( !split )
				{
					SplitBubble();
					split = true;
				}
			} else 
			{
				split = false;
			}
			break;
		}
	case COMMAND_ACTION2:
		{
			if( (bool)data )
			{
				absorbing = true;
			} else 
			{
				absorbing = false;
				absorbed = false;
			}
			break;
		}
	case COMMAND_ACTION3:
		{
			Object* obj = ObjectTemplateManager::Instance()->Create( "Bubble" );
			obj->GetProperty<float>("Width") = 40;
			obj->GetProperty<float>("Height") = 40;
			obj->GetProperty<float>("PosX") = posX.Get();
			obj->GetProperty<float>("PosY") = posY.Get() + 50;
			obj->InitComponents();
			ObjectManager::Instance()->AddObject( obj );
			break;
		}
	case COMMAND_ACTION4:
		{
			std::cout << posX.Get() << " " << posY.Get() << std::endl;
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
		b2Contact *contact = (b2Contact*)data;
		Object* collidedWith;
		if( contact->GetFixtureA()->GetUserData() == go )
		{
			collidedWith = (Object*)contact->GetFixtureB()->GetUserData();
		} else
		{
			collidedWith = (Object*)contact->GetFixtureA()->GetUserData();
		}

		if( collidedWith->HasComponent("BubbleAbsorbable") || collidedWith->HasComponent("TrackTrain") )
		{
			if( (collidedWith->GetProperty<float>("PosY") - posY.Get()) > 0 )
			{
				jumping = false;
			}
		}

		b2Manifold *manifold = contact->GetManifold();
		for( int i = 0; i < manifold->pointCount; ++i )
		{
			b2ManifoldPoint point = manifold->points[i];
			if( manifold->localNormal.y == -1 && manifold->localNormal.x == 0 )
			{
				jumping = false;
			}
		}
	} 
}

void BallCoreController::SplitBubble()
{
	if( spriteRadius.Get() <= 20 ) 
		return;

	float splitRadius = spriteRadius.Get()/2;
	float newCoreRadius = splitRadius;
	float newBubbleRadius = splitRadius;
	if( newCoreRadius < 20 )
	{
		float diff = 20 - newCoreRadius;
		newCoreRadius += diff;
		newBubbleRadius -= diff;
	}

	spriteRadius.Set( newCoreRadius );
	height.Set( newCoreRadius );

	Object* obj = ObjectTemplateManager::Instance()->Create( "Bubble" );
	obj->GetProperty<float>("Width") = newBubbleRadius;
	obj->GetProperty<float>("Height") = newBubbleRadius;
	obj->GetProperty<float>("PosX") = posX.Get();
	obj->GetProperty<float>("PosY") = posY.Get() + newBubbleRadius;
	obj->InitComponents();
	ObjectManager::Instance()->AddObject( obj );

}

void BallCoreController::OnWidthChanged( const float &oldValue, const float &newValue )
{
	//Calculate new zoom
	float zoom = newValue/70;

	cameraZoom = zoom;
}