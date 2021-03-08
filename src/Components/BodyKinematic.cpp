#include "Components/BodyKinematic.h"
#include "Object.h"
#include "PhysicsManager.h"
#include <Box2D\Box2D.h>

BodyKinematic::BodyKinematic(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body = NULL;

	spriteWidth = go->AddProperty<float>("SpriteWidth",32.0f);
	spriteHeight = go->AddProperty<float>("SpriteHeight",32.0f);

	posX = go->AddProperty<float>("PosX",0.0f);
	posY = go->AddProperty<float>("PosY",0.0f);
	
	velocityX = go->AddProperty<float>("VelocityX",0.0f);
	velocityY = go->AddProperty<float>("VelocityY",0.0f);

	initialVelX = go->AddProperty<float>("InitialVelX",0.0f);
	initialVelY = go->AddProperty<float>("InitialVelY",0.0f);
	initialAngleVel = go->AddProperty<float>("InitialAngleVel",0.0f);

	rotation = go->AddProperty<float>("Rotation",0.0f);
	fixedRotation = go->AddProperty<bool>("FixedRotation",false);

	physBody = go->AddProperty<b2Body**>("PhysBody", &body);
	staticObject = go->AddProperty<bool>("StaticObject",false);
}

BodyKinematic::~BodyKinematic()
{
	if(body)
		PhysicsManager::Instance()->DestroyBody( body );
	physBody.Set(NULL);
}

void BodyKinematic::Init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set( (posX.Get())/PTM_RATIO, posY.Get()/PTM_RATIO );
	bodyDef.angle = rotation*DEGTORAD;
	body = PhysicsManager::Instance()->CreateBody( &bodyDef );
	physBody.Set( &body );
	body->SetUserData( go );
	body->SetFixedRotation( fixedRotation.Get() );

	body->SetLinearVelocity( b2Vec2( initialVelX.Get(), initialVelY.Get() ) );
	//body->SetAngularVelocity(util::Random(-initialAngleVel.Get(), initialAngleVel.Get() ));
	staticObject.Set(false);
}

void BodyKinematic::Update(float delta)
{
	posX.Set( body->GetPosition().x * PTM_RATIO, false );
	posY.Set( body->GetPosition().y * PTM_RATIO, false );
	rotation.Set( body->GetAngle()*(180/PI) , false); //radian to degree
	velocityX.Set( body->GetLinearVelocity().x, false );
	velocityY.Set( body->GetLinearVelocity().y, false );
}

void BodyKinematic::Draw(sf::RenderWindow &window)
{

}

void BodyKinematic::ExecuteCommand(int command, void* data)
{

}

void BodyKinematic::ExecuteEvent(int event, void* data)
{

}