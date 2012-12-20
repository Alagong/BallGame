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
GameManager* GameManager::gameManagerInstance;
GameManager* GameManager::Instance()
{
	if( !gameManagerInstance )
		gameManagerInstance = new GameManager();
	return gameManagerInstance;
}

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Run()
{
	std::string title("Ball Game");
	DrawManager::Instance()->CreateWindow( title, 1366, 768, true, 60 );

	ComponentRegistrator::Register( *ComponentFactory::Instance() );

	ObjectTemplateManager::Instance()->LoadObjects( std::string("../resources/data/objects/") );

	Object* obj = ObjectTemplateManager::Instance()->Create("Test");
	obj->InitComponents();
	ObjectManager::Instance()->AddObject( obj );

	while( DrawManager::Instance()->IsWindowOpen() )
	{
		sf::Event event;
		DrawManager::Instance()->Window()->pollEvent( event );
		ObjectManager::Instance()->UpdateObjects();
		DrawManager::Instance()->Render();
	}
}
