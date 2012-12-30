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
	DrawManager::Instance()->CreateWindow( title, 600, 599, true, 60 );

	ComponentRegistrator::Register( *ComponentFactory::Instance() );

	ObjectTemplateManager::Instance()->LoadObjects( std::string("../resources/data/objects/") );

	Object* obj = ObjectTemplateManager::Instance()->Create("Test");
	obj->InitComponents();
	ObjectManager::Instance()->AddObject( obj );

	Object* obj3 = ObjectTemplateManager::Instance()->Create("Bubble");
	obj3->GetProperty<float>("PosX") = 300;
	obj3->InitComponents();
	ObjectManager::Instance()->AddObject( obj3 );

	Object* obj2 = ObjectTemplateManager::Instance()->Create("Wall");
	obj2->GetProperty<float>("PosX") = 300;
	obj2->GetProperty<float>("PosY") = 300;
	obj2->InitComponents();
	ObjectManager::Instance()->AddObject( obj2 );

	while( DrawManager::Instance()->IsWindowOpen() )
	{
		input->ResetKeyStates();
		sf::Event event;
		while( DrawManager::Instance()->Window()->pollEvent( event ) )
		{
			input->PollInput( event );
		}

		PhysicsManager::Instance()->Step();
		ObjectManager::Instance()->UpdateObjects();

		DrawManager::Instance()->Render();
	}
}
