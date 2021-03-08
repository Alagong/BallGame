#include "Components/TrackTrain.h"
#include <iostream>
#include <boost/bind.hpp>
#include "defines.h"
#include <math.h>
#include "PhysicsManager.h"
#include "ObjectManager.h"

TrackTrain::TrackTrain(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	startWaypointID = go->AddProperty<int>("StartWaypointID",0);

	width = go->AddProperty<float>("Width",32);
	height = go->AddProperty<float>("Height",32);

	posX = go->AddProperty<float>("PosX",0);
	posY = go->AddProperty<float>("PosY",0);

	rotation = go->AddProperty<float>("Rotation",0);
	speed = go->AddProperty<float>("Speed",1.0f);
	physBody = go->AddProperty<b2Body**>("PhysBody", &body);
	
	staticObject = go->AddProperty<bool>("StaticObject",false);
	activated = go->AddProperty<bool>("Activated",true);
	compInitialized = false;
	nextWaypoint = NULL;
	
}

TrackTrain::~TrackTrain()
{
	PhysicsManager::Instance()->DestroyBody(body);
}

void TrackTrain::Init()
{
	SetNewWaypoint(startWaypointID.Get());
	posX.Set(nextWaypoint->GetX()+1);
	posY.Set(nextWaypoint->GetY());
	{
		bodyDef.type = b2_kinematicBody;
		bodyDef.position.Set(posX.Get()/PTM_RATIO, posY.Get()/PTM_RATIO);
		body = PhysicsManager::Instance()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox( (width.Get()/2)/PTM_RATIO - (1/PTM_RATIO) , (height.Get()/2)/PTM_RATIO - (1/PTM_RATIO));
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.userData = go;
		body->CreateFixture(&fixtureDef);
		body->SetUserData(go);
	}
	//body->SetTransform( b2Vec2(posX.Get()/PTM_RATIO, posY.Get()/PTM_RATIO), body->GetAngle());

/*	{
		pjd.Initialize( pState->GetGroundBody(), body, b2Vec2(0.0f, 5.0f), b2Vec2(1.0f, 0.0f));
		pjd.maxMotorForce = 1000.0f;
		pjd.enableMotor = true;
		pjd.lowerTranslation = -10.0f;
		pjd.upperTranslation = 10.0f;
		pjd.enableLimit = true;
		(b2PrismaticJoint*)pState->box2dWorld->CreateJoint(&pjd);
		
	}*/

	if( activated.Get() )
	{ // Find first waypoint
		b2Vec2 p = body->GetTransform().p;
		float angX = nextWaypoint->GetX()/PTM_RATIO - p.x;
		float angY = nextWaypoint->GetY()/PTM_RATIO - p.y;
		float magnitude = sqrt(angX*angX+angY*angY);
		body->SetLinearVelocity(b2Vec2( (angX/magnitude)*speed, (angY/magnitude)*speed ) );
	}

	compInitialized = true;
	staticObject.Set(false);
	startWaypointID.ValueChanged().connect(boost::bind(&TrackTrain::OnStartWaypointChanged,this,_1,_2));
	activated.ValueChanged().connect(boost::bind(&TrackTrain::OnActivatedChanged,this,_1,_2));
}

void TrackTrain::Update(float delta)
{

	if( !activated.Get() ) return;
	if(nextWaypoint != NULL)
	{
		b2Vec2 p = body->GetTransform().p;
		b2Vec2 v = body->GetLinearVelocity();

		float destX = nextWaypoint->GetX();
		float destY = nextWaypoint->GetY();

		//calc dot product
		float wpAngX = destX/PTM_RATIO - p.x;
		float wpAngY = destY/PTM_RATIO - p.y;
		float wpMagnitude = sqrt(wpAngX*wpAngX+wpAngY*wpAngY);
		b2Vec2 angToWp(wpAngX/wpMagnitude, wpAngY/wpMagnitude );
		float dot = (angToWp.x * movingDirection.x) + (angToWp.y * movingDirection.y);

		if( dot <= 0.0f )
		{

			SetNewWaypoint(nextWaypoint->GetNextWaypointID());
			if(nextWaypoint == NULL)
			{
				posX.Set(lastWaypointPos.x/PTM_RATIO);
				posY.Set(lastWaypointPos.x/PTM_RATIO);
				body->SetLinearVelocity(b2Vec2(0.0f,0.0f));
			} else 
			{
				posX.Set(nextWaypoint->GetX()+1);
				posY.Set(nextWaypoint->GetY());
				body->SetTransform( b2Vec2(lastWaypointPos.x/PTM_RATIO, lastWaypointPos.y/PTM_RATIO), body->GetAngle());
				float angX = nextWaypoint->GetX()/PTM_RATIO - lastWaypointPos.x/PTM_RATIO;
				float angY = nextWaypoint->GetY()/PTM_RATIO - lastWaypointPos.y/PTM_RATIO;
				float magnitude = sqrt(angX*angX+angY*angY);
				movingDirection = b2Vec2( (angX/magnitude), (angY/magnitude) ) ;
				if(abs(movingDirection.x) < 0.005) movingDirection.x = 0;
				if(abs(movingDirection.y) < 0.005) movingDirection.y = 0;
				body->SetLinearVelocity(b2Vec2( movingDirection.x*speed , movingDirection.y*speed ) );
			}
		}
	}
	posX.Set( body->GetPosition().x * PTM_RATIO );
	posY.Set( body->GetPosition().y * PTM_RATIO );
}

void TrackTrain::Draw(sf::RenderWindow &window)
{

}

void TrackTrain::ExecuteCommand(int command, void* data )
{
	
}

void TrackTrain::ExecuteEvent(int event, void* data)
{

}

void TrackTrain::SetNewWaypoint(int id)
{
	if(nextWaypoint != NULL)
	{
		lastWaypointPos.x = nextWaypoint->GetX();
		lastWaypointPos.y = nextWaypoint->GetY();
		if(nextWaypoint->GetNewSpeed() != 0)
		{
			speed.Set(nextWaypoint->GetNewSpeed());
		}
	}

	nextWaypoint = ObjectManager::Instance()->GetWaypointByID(id);
}

void TrackTrain::OnStartWaypointChanged(const int &oldValue, const int &newValue)
{
	SetNewWaypoint(newValue);
	if(nextWaypoint != NULL)
	{
		posX.Set(nextWaypoint->GetX()+1);
		posY.Set(nextWaypoint->GetY());
		body->SetTransform( b2Vec2(lastWaypointPos.x/PTM_RATIO, lastWaypointPos.y/PTM_RATIO), body->GetAngle());
	}
}

void TrackTrain::OnActivatedChanged( const bool &oldValue, const bool &newValue )
{
	b2Vec2 p = body->GetTransform().p;
	float angX = nextWaypoint->GetX()/PTM_RATIO - p.x;
	float angY = nextWaypoint->GetY()/PTM_RATIO - p.y;
	float magnitude = sqrt(angX*angX+angY*angY);
	body->SetLinearVelocity(b2Vec2( (angX/magnitude)*speed, (angY/magnitude)*speed ) );
}
