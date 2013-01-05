#include "Components/PlayerInput.h"
#include "ComponentEngine\CompEvents.h"
#include "ComponentEngine\CompCommands.h"
#include "Input.h"
#include "Object.h"
PlayerInput::PlayerInput(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	jumpPressed = false;
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::Init()
{
	jumpPressed = false;
	//std::cout << "22 " << std::endl;
}

void PlayerInput::Update(float delta)
{
	if( Input::KeyPressed( sf::Keyboard::Space ) )
	{
		go->ExecuteCommand( COMMAND_JUMP );
	}

/*	if( Input::KeyPressed( sf::Keyboard::Right ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 0;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
		delete moveData;
	}
	if( Input::KeyPressed( sf::Keyboard::Up ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 1;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
		delete moveData;
	}
	if( Input::KeyPressed( sf::Keyboard::Left ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 2;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
		delete moveData;
	}
	if( Input::KeyPressed( sf::Keyboard::Down ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 3;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
		delete moveData;
	}

	if( Input::KeyReleased( sf::Keyboard::Right ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 0;
		moveData->start = false;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyReleased( sf::Keyboard::Up ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 1;
		moveData->start = false;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyReleased( sf::Keyboard::Left ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 2;
		moveData->start = false;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyReleased( sf::Keyboard::Down ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 3;
		moveData->start = false;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}*/

	if( Input::KeyPressed( sf::Keyboard::Z ) )
	{
		go->ExecuteCommand( COMMAND_ACTION1, 0, (void*)true );
	}

	if( Input::KeyReleased( sf::Keyboard::Z ) )
	{
		go->ExecuteCommand( COMMAND_ACTION1, 0, (void*)false );
	}

	if( Input::KeyPressed( sf::Keyboard::X ) )
	{
		go->ExecuteCommand( COMMAND_ACTION2, 0, (void*)true );
	}

	if( Input::KeyReleased( sf::Keyboard::X ) )
	{
		go->ExecuteCommand( COMMAND_ACTION2, 0, (void*)false );
	}

	if( Input::KeyPressed( sf::Keyboard::F1 ) )
	{
		go->ExecuteCommand( COMMAND_ACTION3, 0, (void*)true );
	}
	if( Input::KeyPressed( sf::Keyboard::F2 ) )
	{
		go->ExecuteCommand( COMMAND_ACTION4, 0, (void*)true );
	}
}

void PlayerInput::Draw(sf::RenderWindow &window)
{

}

void PlayerInput::ExecuteCommand(int command, void* data)
{
}

void PlayerInput::ExecuteEvent(int event, void* data)
{

}