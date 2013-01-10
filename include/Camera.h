#pragma once

namespace sf
{
	class RenderWindow;
};
#include <SFML/System/Vector2.hpp>
#include "Timer.h"
class Camera
{
private:
	static Camera* cameraInstance;

	sf::RenderWindow* window;
	sf::Vector2f center;
	sf::Vector2f screenSize;
	int activeCameraID;


	float zoom;
	float zoomFrom;
	float zoomTo;

	Timer zoomTimer;
	float zoomTime;
	bool zooming;
	

	void SetWindowPtr( sf::RenderWindow* windowPtr );
public:
	static Camera* Instance();
	Camera();

	void Update( float delta );

	sf::Vector2f GetCenter() const {return center;}
	void SetCenter( sf::Vector2f center );

	void SetCameraBounds( sf::Vector2f bounds );
	sf::Vector2f GetCameraBounds();
	void UpdateWindowView();

	void Zoom( float scale, float time = 0 );

	int GetActiveCameraID();
	void SetActiveCameraID(int ID);
};