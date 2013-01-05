#include "Components/SphereShape.h"
#include "Object.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <boost/bind.hpp>
SphereShape::SphereShape(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posX = go->AddProperty<float>("PosX", 0.0 );
	posY = go->AddProperty<float>("PosY", 0.0 );
	width = go->AddProperty<float>("Width", 0.0 );
	height = go->AddProperty<float>("Height", 0.0 );

	sphereColorR = go->AddProperty<int>("SphereColorR", 0.0 );
	sphereColorG = go->AddProperty<int>("SphereColorG", 0.0 );
	sphereColorB = go->AddProperty<int>("SphereColorB", 0.0 );
	sphereColorA = go->AddProperty<int>("SphereColorA", 0.0 );

	outlineThickness = go->AddProperty<float>("OutLineThickness", 0 );
}

SphereShape::~SphereShape()
{

}

void SphereShape::Init()
{
	width.ValueChanged().connect(boost::bind(&SphereShape::OnWidthChanged,this,_1,_2));
	height.ValueChanged().connect(boost::bind(&SphereShape::OnHeightChanged,this,_1,_2));

	startWidth = width.Get();
	startHeight = height.Get();

	circle.setRadius( width/2 );
	circle.setFillColor( sf::Color( sphereColorR.Get(),sphereColorG.Get(),sphereColorB.Get(),sphereColorA.Get() ) );
	circle.setOrigin( width.Get()/2,height.Get()/2);

	circle.setOutlineThickness( outlineThickness.Get() );
	circle.setOutlineColor( sf::Color( sphereColorR.Get(), sphereColorG.Get(), sphereColorB.Get() ) );
}

void SphereShape::Update(float delta)
{

}

void SphereShape::Draw(sf::RenderWindow* window)
{
	circle.setPosition( posX.Get(), posY.Get() );
	window->draw( circle );
}

void SphereShape::ExecuteCommand(int command, void* data)
{

}

void SphereShape::ExecuteEvent(int event, void* data)
{

}

void SphereShape::OnWidthChanged(const float &oldvalue, const float &newValue)
{
	circle.setScale( width.Get() / startWidth, height.Get() / startHeight );
}

void SphereShape::OnHeightChanged(const float &oldvalue, const float &newValue)
{
	circle.setScale( width.Get() / startWidth, height.Get() / startHeight );	
}