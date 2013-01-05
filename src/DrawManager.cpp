#include "DrawManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ObjectManager.h"
#include "Camera.h"
DrawManager* DrawManager::drawManagerInstance;
DrawManager* DrawManager::Instance()
{
	if( !drawManagerInstance )
	{
		drawManagerInstance = new DrawManager();
	}
	return drawManagerInstance;
}

void DrawManager::CreateWindow( std::string& title, int resx, int resy, bool windowed, int fps )
{
	window = new sf::RenderWindow(sf::VideoMode(resx,resy),title, (windowed ? sf::Style::Close : sf::Style::Fullscreen) );
	window->setVerticalSyncEnabled( false );
	window->setFramerateLimit( fps );
	font.loadFromFile("arial.ttf");
	info.setFont( font );
	info.setColor( sf::Color(255,0,0) );
	info.setCharacterSize( 16 );
	info.setString( "testtest" );
}

bool DrawManager::IsWindowOpen()
{
	return window->isOpen();
}

void DrawManager::Render()
{
	
	window->clear();
	
	ObjectManager::Instance()->DrawObjects( window );

	//info.setPosition( Camera::Instance()->GetCenter().x - Camera::Instance()->GetCameraBounds().x + 20, Camera::Instance()->GetCenter().y - Camera::Instance()->GetCameraBounds().y + 20 );
	//window->draw(info);
	
	window->display();
}