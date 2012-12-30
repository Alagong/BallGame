#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class Input
{
private:
	static bool keysPressed[ sf::Keyboard::KeyCount ];
	static bool keysReleased[ sf::Keyboard::KeyCount ];
public:
	Input();
	void ResetKeyStates();
	void PollInput( sf::Event& event );
	static bool IsKeyDown( sf::Keyboard::Key key );

	static bool KeyPressed( sf::Keyboard::Key key );
	static bool KeyReleased( sf::Keyboard::Key key );
};