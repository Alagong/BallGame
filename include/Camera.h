#pragma once

#include <SFML/System/Vector2.hpp>
#include "Timer.h"

namespace sf
{
	class RenderWindow;
};

class Camera
{
private:
	static Camera* s_cameraInstance;

	sf::RenderWindow* m_window;
	sf::Vector2f m_center;

	sf::Vector2f m_screenSize;
	int m_activeCameraId;

	float m_zoom;
	float m_zoomFrom;
	float m_zoomTo;
	Timer m_zoomTimer;
	float m_zoomTime;
	bool m_zooming;

	void SetWindowPtr( sf::RenderWindow* windowPtr );
public:

	static Camera* Instance();

	Camera();

	void Update( float delta );

	sf::Vector2f GetCenter() const;
	void SetCenter( sf::Vector2f center );

	int GetActiveCameraId();
	void SetActiveCameraId(int cameraId);

	void Zoom( float scale, float time = 0 );

	void SetCameraBounds( sf::Vector2f bounds );
	sf::Vector2f GetCameraBounds();
};