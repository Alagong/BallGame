#include "Components/GradientRectangle.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
GradientRectangle::GradientRectangle(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posX = go->AddProperty<float>("PosX",0.0f);
	posY = go->AddProperty<float>("PosY",0.0f);

	width = go->AddProperty<float>("Width",0);
	height = go->AddProperty<float>("Height",0);

	gradientDirection = go->AddProperty<int>("GradientDirection", 0 );
	
	gradientColorAR = go->AddProperty<int>("GradientColorAR", 255 );
	gradientColorAG = go->AddProperty<int>("GradientColorAG", 255 );
	gradientColorAB = go->AddProperty<int>("GradientColorAB", 255 );

	
	gradientColorBR = go->AddProperty<int>("GradientColorBR", 255 );
	gradientColorBG = go->AddProperty<int>("GradientColorBG", 255 );
	gradientColorBB = go->AddProperty<int>("GradientColorBB", 255 );
}

GradientRectangle::~GradientRectangle()
{

}

void GradientRectangle::Init()
{
	if( gradientDirection.Get() == 0 )
	{
		rectangle[0] = sf::Vertex( sf::Vector2f( posX.Get() - width.Get()/2, posY.Get() - height.Get()/2), sf::Color( gradientColorAR.Get(),gradientColorAB.Get(),gradientColorAG.Get() ) );
		rectangle[1] = sf::Vertex( sf::Vector2f( posX.Get() + width.Get()/2, posY.Get() - height.Get()/2),  sf::Color( gradientColorAR.Get(),gradientColorAB.Get(),gradientColorAG.Get() ) );
		rectangle[2] = sf::Vertex( sf::Vector2f( posX.Get() + width.Get()/2, posY.Get() + height.Get()/2),  sf::Color( gradientColorBR.Get(),gradientColorBB.Get(),gradientColorBG.Get() ) );
		rectangle[3] = sf::Vertex( sf::Vector2f( posX.Get() - width.Get()/2, posY.Get() + height.Get()/2),  sf::Color( gradientColorBR.Get(),gradientColorBB.Get(),gradientColorBG.Get() ) );
	}

	lines[0] = sf::Vertex( sf::Vector2f( posX.Get() - width.Get()/2, posY.Get() - height.Get()/2), sf::Color( 255,255,255 ) );
	lines[1] = sf::Vertex( sf::Vector2f( posX.Get() + width.Get()/2, posY.Get() - height.Get()/2), sf::Color( 255,255,255 ) );
	lines[2] = sf::Vertex( sf::Vector2f( posX.Get() + width.Get()/2, posY.Get() + height.Get()/2), sf::Color( 255,255,255 ) );
	lines[3] = sf::Vertex( sf::Vector2f( posX.Get() - width.Get()/2, posY.Get() + height.Get()/2), sf::Color( 255,255,255 ) );
	lines[4] = sf::Vertex( sf::Vector2f( posX.Get() - width.Get()/2, posY.Get() - height.Get()/2), sf::Color( 255,255,255 ) );
}

void GradientRectangle::Update(float delta)
{

}

void GradientRectangle::Draw(sf::RenderWindow* window)
{
	window->draw( rectangle, 4, sf::Quads );
	window->draw( lines, 5, sf::LinesStrip );
}

void GradientRectangle::ExecuteCommand(int command, void* data)
{

}

void GradientRectangle::ExecuteEvent(int event, void* data)
{

}
