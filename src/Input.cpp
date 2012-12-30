#include "Input.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
bool Input::keysPressed[ sf::Keyboard::KeyCount ];
bool Input::keysReleased[ sf::Keyboard::KeyCount ];

Input::Input()
{
	ResetKeyStates();
}

bool Input::IsKeyDown( sf::Keyboard::Key key )
{
	return sf::Keyboard::isKeyPressed( key );
}

void Input::ResetKeyStates()
{
	for( int i = 0; i < sf::Keyboard::KeyCount; ++i )
	{
		keysPressed[i] = false;
		keysReleased[i] = false;
	}
}

void Input::PollInput( sf::Event& event )
{
	if( event.type == sf::Event::KeyPressed )
	{
		std::cout << "Key pressed" << std::endl;
		keysPressed[ event.key.code ] = true;
	}
	else if ( event.type == sf::Event::KeyReleased )
	{
		keysReleased[ event.key.code ] = true;
	}
}

bool Input::KeyPressed( sf::Keyboard::Key key )
{
	return keysPressed[ key ];
}

bool Input::KeyReleased( sf::Keyboard::Key key )
{
	return keysReleased[ key ];
}