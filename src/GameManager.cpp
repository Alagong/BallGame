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
#include "Timer.h"
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
	fpsTimer = new Timer();
}

GameManager::~GameManager()
{
	delete fpsTimer;
}

void GameManager::Run()
{
	std::string title("Ball Game");
	DrawManager::Instance()->CreateWindow( title, 1360, 768, true, 60 );

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
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				windowPtr->close();
			}
			input->PollInput( event );
		}

		float delta = fpsTimer->GetMilliseconds();
		fpsTimer->Restart();

		PhysicsManager::Instance()->Step();
		Camera::Instance()->Update( delta );
		ObjectManager::Instance()->UpdateObjects( delta );

		DrawManager::Instance()->Render();
	}
}
