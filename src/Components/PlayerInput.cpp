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

	if( Input::KeyPressed( sf::Keyboard::Right ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 0;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyPressed( sf::Keyboard::Up ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 1;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyPressed( sf::Keyboard::Left ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 2;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
	}
	if( Input::KeyPressed( sf::Keyboard::Down ) )
	{
		CommandData_Move* moveData = new CommandData_Move();
		moveData->direction = 3;
		moveData->start = true;
		go->ExecuteCommand( COMMAND_MOVE, 0 , moveData );
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