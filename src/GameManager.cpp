#include "GameManager.h"
#include "Camera.h"
#include "DrawManager.h"
#include <string>
#include "Object.h"
#include "ComponentEngine/ComponentFactory.h"
#include "ObjectManager.h"
#include "ComponentEngine/ComponentRegistrator.h"
#include "ObjectTemplateManager.h"
#include <iostream>
#include "AnimationContainer.h"
#include "PhysicsManager.h"
#include "Input.h"
#include "MapLoader.h"
GameManager* GameManager::gameManagerInstance;
GameManager* GameManager::Instance()
{
	if( !gameManagerInstance )
		gameManagerInstance = new GameManager();
	return gameManagerInstance;
}

GameManager::GameManager()
{
	input = new Input();
	input->ResetKeyStates();
}

GameManager::~GameManager()
{

}

void GameManager::Run()
{
	std::string title("Ball Game");
	DrawManager::Instance()->CreateWindow( title, 1366, 768, false, 60 );

	ComponentRegistrator::Register( *ComponentFactory::Instance() );

	ObjectTemplateManager::Instance()->LoadObjects( std::string("../resources/data/objects/") );

	MapLoader loader;
	loader.LoadMap( std::string( "../resources/data/maps/protomap/" ) );
	ObjectManager::Instance()->InitAllObjects();

	Camera::Instance()->SetActiveCameraID( 0 );

	sf::RenderWindow* windowPtr = DrawManager::Instance()->Window();

	while( windowPtr->isOpen() )
	{
		input->ResetKeyStates();
		sf::Event event;
		while( windowPtr->pollEvent( event ) )
		{
			input->PollInput( event );
		}

		PhysicsManager::Instance()->Step();
		ObjectManager::Instance()->UpdateObjects();

		DrawManager::Instance()->Render();
	}
}
