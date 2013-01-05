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

	int activeCameraID;
public:
	static Camera* Instance();
	Camera();

	void SetWindowPtr( sf::RenderWindow* windowPtr );

	sf::Vector2f GetCenter() const {return center;}
	void SetCenter( sf::Vector2f center );

	void SetCameraWidth(int width);
	void SetCameraHeight(int height);
	void SetCameraBounds( sf::Vector2f bounds );
	sf::Vector2f GetCameraBounds();
	void UpdateWindowView();

	void Zoom( float scale );

	int GetActiveCameraID();
	void SetActiveCameraID(int ID);
};