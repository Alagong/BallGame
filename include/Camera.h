#pragma once

namespace sf
{
	class RenderWindow;
};
#include <SFML/System/Vector2.hpp>

class Camera
{
private:
	static Camera* cameraInstance;

	sf::RenderWindow* window;
	sf::Vector2f center;
	sf::Vector2f screenSize;
	float zoom;
public:
	static Camera* Instance();

	void SetWindowPtr( sf::RenderWindow* windowPtr );

	sf::Vector2f GetCenter() const {return center;}
	void SetCenter( sf::Vector2f center );

	void UpdateWindowView();

};