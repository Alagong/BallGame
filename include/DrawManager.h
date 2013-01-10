#pragma once

/*
**
*/
#include <string>
namespace sf
{
	class RenderWindow;
};
class DrawManager
{
private:
	sf::RenderWindow *window;
	static DrawManager*	drawManagerInstance;

public:
	static DrawManager* Instance();
	void CreateWindow(std::string& title, int resx, int resy, bool windowed = true, int fps = 60);
	sf::RenderWindow* Window() { return window;}
	bool IsWindowOpen();

	void Render();
};