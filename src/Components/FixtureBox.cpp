#include "Components/FixtureBox.h"
#include <boost/bind.hpp>
#include "Object.h"
#include <Box2D\Box2D.h>
#include "ComponentEngine\CompEvents.h"
FixtureBox::FixtureBox(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	body           = NULL;
	width    = go->AddProperty<float>("Width",0);
	height   = go->AddProperty<float>("Height",0);
	collisionWidth    = go->AddProperty<float>("CollisionWidth",-1);
	collisionHeight   = go->AddProperty<float>("CollisionHeight",-1);
	posX           = go->AddProperty<float>("PosX",0);
	posY           = go->AddProperty<float>("PosY",0);
	collisionOffsetX        = go->AddProperty<float>("CollisionOffsetX",0);
	collisionOffsetY        = go->AddProperty<float>("CollisionOffsetY",0);
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

FixtureBox::~FixtureBox()
{
	if(physBody.Get() != NULL)
		body->DestroyFixture(fixture);
}

void FixtureBox::Init()
{
	isSensor.ValueChanged().connect(boost::bind(&FixtureBox::OnisSensorChanged,this,_1,_2));

/*	if(parentId.Get() != 0)
	{
		//Find parent object
		Object* obj = pState->GetObjectByID(parentId.Get());
		if(obj != NULL)
		{
			if( obj->HasComponent("Physics_DynamicBody") || obj->HasComponent("Physics_KinematicBody") )
			{
				//Get its body
				body = *obj->GetProperty<b2Body**>("PhysBody");
			}
		}
	} 
	else
	{*/
		body = *physBody.Get();
	//}

	//If collisionwidth/height is not defined, set it as the same as spritewidth
	if(collisionWidth.Get() <= 0)
		collisionWidth.Set(width.Get());
	if(collisionHeight.Get() <= 0)
		collisionHeight.Set(height.Get());

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox( (collisionWidth.Get()/2)/PTM_RATIO - (1/PTM_RATIO) , (collisionHeight.Get()/2)/PTM_RATIO - (1/PTM_RATIO),
		b2Vec2(collisionOffsetX.Get()/PTM_RATIO,collisionOffsetY.Get()/PTM_RATIO),0.0f);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
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

void FixtureBox::Update(int delta)
{
	//Update position and rotation from the fixture
	const b2AABB &aabb = fixture->GetAABB(0);
	posX.Set( aabb.GetCenter().x * PTM_RATIO, false );
	posY.Set( aabb.GetCenter().y * PTM_RATIO, false );
	rotation.Set(body->GetAngle()*(180/PI), false); //radian to degree
}

void FixtureBox::Draw(sf::RenderWindow &window)
{

}

void FixtureBox::ExecuteCommand(int command, void* data)
{

}

void FixtureBox::ExecuteEvent(int event, void* data)
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

void FixtureBox::OnisSensorChanged(const bool &oldvalue, const bool &newValue)
{
	fixture->SetSensor(newValue);
}