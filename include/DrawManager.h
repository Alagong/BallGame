#pragma once

/*
**
*/
#include <string>
namespace sf
{
	class RenderWindow;
};
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
class DrawManager
{
private:
	sf::RenderWindow *window;
	static DrawManager*	drawManagerInstance;
	sf::Text info;
	sf::Font font;
public:
	static DrawManager* Instance();
	void CreateWindow(std::string& title, int resx, int resy, bool windowed = true, int fps = 60);
	sf::RenderWindow* Window() { return window;}
	bool IsWindowOpen();

	void Render();
};