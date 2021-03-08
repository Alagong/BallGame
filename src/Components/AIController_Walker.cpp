#include "Components/AIController_Walker.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include <Box2D\Box2D.h>
#include "Callbacks.h"
#include "PhysicsManager.h"
#include "Timer.h"
AIController_Walker::AIController_Walker(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{

	posX = go->AddProperty<float>("PosX",0.0f);
	posY = go->AddProperty<float>("PosY",0.0f);
	spriteWidth = go->AddProperty<float>("SpriteWidth",32);
	spriteHeight = go->AddProperty<float>("SpriteHeight",32);

	physBody = go->AddProperty<b2Body**>("PhysBody", &body);

	tilted = true;
	groundFound = true;

	tiltedTimer = new Timer();

}

AIController_Walker::~AIController_Walker()
{
	delete tiltedTimer;
}

void AIController_Walker::Init()
{
	body = *physBody.Get();
}

void AIController_Walker::Update(float delta)
{
	if( tilted )
	{
		//Try to find ground to deploy on
		if( !groundFound )
		{
			if( body->GetLinearVelocity().Length() <= 0 )
			{
				tiltedTimer->Restart();
				groundFound = findGround();
			}
		} 
		else if( tiltedTimer->GetSeconds() > 2.0f )
		{
			tilted = false;
			groundFound = findGround();
			if( groundFound )
			{
				tilted = false;
			}
		}
	} else 
	{
		//Deploy 
		std::cout << "deployed" << std::endl;
	}
}

void AIController_Walker::Draw(sf::RenderWindow &window)
{

}

void AIController_Walker::ExecuteCommand(int command, void* data)
{

}

void AIController_Walker::ExecuteEvent(int event, void* data)
{

}

bool AIController_Walker::findGround()
{
	RayCastFirstBodyCallback callback;
	PhysicsManager::Instance()->GetWorld()->RayCast( &callback, body->GetPosition(), body->GetPosition() + 
		b2Vec2( 0, (spriteHeight.Get() + 5 )/PTM_RATIO ) );

	return callback.m_hit;
}