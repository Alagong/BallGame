#include "Components/FixtureSphere.h"
#include <boost/bind.hpp>
#include "Object.h"
#include <Box2D\Box2D.h>
#include "ComponentEngine\CompEvents.h"
FixtureSphere::FixtureSphere(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body           = NULL;
	spriteRadius    = go->AddProperty<float>("Width",32);
	collisionRadius    = go->AddProperty<float>("CollisionRadius",-1);
	posX           = go->AddProperty<float>("PosX",0);
	posY           = go->AddProperty<float>("PosY",0);

	isSensor       = go->AddProperty<bool>("IsSensor",false);
	density        = go->AddProperty<float>("Density",0.0f);
	friction       = go->AddProperty<float>("Friction",0.0f);
	rotation       = go->AddProperty<float>("Rotation",0);
	physBody       = go->AddProperty<b2Body**>("PhysBody", &body);
	parentObject   = go->AddProperty<Object*>("ParentObject",NULL);
	parentId       = go->AddProperty<int>("ParentId",0);
	collisionGroup = go->AddProperty<int>("CollisionGroup",0);	
	categoryBits = go->AddProperty<int>("CategoryBits",-1);
	fixtureBox = go->AddProperty<b2Fixture**>("Fixture",&fixture);
	maskBits = go->AddProperty<int>("MaskBits",-1);
}

FixtureSphere::~FixtureSphere()
{
	if(physBody.Get() != NULL)
		body->DestroyFixture(fixture);
}

void FixtureSphere::Init()
{
	isSensor.ValueChanged().connect(boost::bind(&FixtureSphere::OnisSensorChanged,this,_1,_2));
	spriteRadius.ValueChanged().connect(boost::bind(&FixtureSphere::OnRadiusChanged,this,_1,_2));


	body = *physBody.Get();


	//If collisionwidth/height is not defined, set it as the same as spritewidth
	if(collisionRadius.Get() <= 0)
		collisionRadius.Set(spriteRadius.Get());

	CreateFixture();

}

void FixtureSphere::CreateFixture()
{
	b2CircleShape circleShape;
	circleShape.m_radius = (collisionRadius.Get()/2)/PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = density.Get();
	fixtureDef.friction = friction.Get();
	fixtureDef.isSensor = isSensor.Get();
	fixtureDef.userData = go;
	if(categoryBits.Get() != -1)
		fixtureDef.filter.categoryBits = categoryBits.Get();
	if(maskBits.Get() != -1)
		fixtureDef.filter.maskBits = 0xFFFF & ~maskBits.Get();
	fixture = body->CreateFixture(&fixtureDef);
	fixture->SetUserData(go);
	
}

void FixtureSphere::Update(int delta)
{
	//Update position and rotation from the fixture
	const b2AABB &aabb = fixture->GetAABB(0);
	posX.Set( aabb.GetCenter().x * PTM_RATIO, false );
	posY.Set( aabb.GetCenter().y * PTM_RATIO, false );
	rotation.Set(body->GetAngle()*(180/PI), false); //radian to degree
}

void FixtureSphere::Draw(sf::RenderWindow &window)
{

}

void FixtureSphere::ExecuteCommand(int command, void* data)
{

}

void FixtureSphere::ExecuteEvent(int event, void* data)
{
	if( event == EVENT_STARTEDCOLLIDING )
	{
		if(!isSensor.Get())
		{

		}
	}
	if( event == EVENT_DIED )
	{
		isSensor = true;
	}
	if( event == EVENT_RESURRECTED )
	{
		isSensor = false;
	}
}

void FixtureSphere::OnisSensorChanged(const bool &oldvalue, const bool &newValue)
{
	fixture->SetSensor(newValue);
}

void FixtureSphere::OnRadiusChanged(const float &oldvalue, const float &newValue)
{
	collisionRadius.Set( newValue );
	body->DestroyFixture( fixture );
	CreateFixture();
}