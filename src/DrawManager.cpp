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
}

bool DrawManager::IsWindowOpen()
{
	return window->isOpen();
}

void DrawManager::Render()
{
	
	window->clear();
	
	ObjectManager::Instance()->DrawObjects( window );
	
	window->display();
}