#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawManager.h"

Camera* Camera::s_cameraInstance;
Camera* Camera::Instance()
{
	if( !s_cameraInstance )
		s_cameraInstance = new Camera();
	return s_cameraInstance;
}

Camera::Camera()
{
	m_activeCameraID = 0;
	m_zoom = 1.0f;
	m_zooming = false;
	m_zoomTime = 1.0f;
	m_zoomFrom = m_zoom;
	m_zoomTo = m_zoom;

	SetWindowPtr( DrawManager::Instance()->Window() );
}

void Camera::Update( float delta )
{
	if( m_zooming && m_zoomTime > m_zoomTimer.GetSeconds() )
	{
		float interpScale = m_zoomTimer.GetSeconds() / m_zoomTime;
		float diff = m_zoomTo - m_zoomFrom;
		float newZoom = m_zoomFrom + (diff * interpScale);
		m_zoom = newZoom;

		sf::View curView = m_window->getView();
		curView.setSize( m_screenSize * m_zoom );
		m_window->setView( curView );

	} else 
	{
		m_zoom = m_zoomTo;
		m_zooming = false;
	}
}

void Camera::SetWindowPtr( sf::RenderWindow* windowPtr )
{
	m_window = windowPtr;
	sf::View curView = m_window->getView();
	m_screenSize = curView.getSize();
}


sf::Vector2f Camera::GetCenter() const
{
	return m_center;
}

void Camera::SetCenter( sf::Vector2f center )
{
	m_center = center;
	sf::View curView = m_window->getView();
	curView.setCenter( m_center );
	m_window->setView( curView );
}

int Camera::GetActiveCameraId()
{
	return m_activeCameraId;
}

void Camera::SetActiveCameraId( int cameraId )
{
	m_activeCameraId = cameraId;
}

void Camera::Zoom( float scale, float time )
{
	if( time != 0 )
	{
		m_zoomTimer.Restart();
		m_zooming = true;
		m_zoomFrom = m_zoom;
		m_zoomTo = scale;
		m_zoomTime = time;
	} else {
		sf::View curView = m_window->getView();
		curView.setSize( m_screenSize * scale );
		m_window->setView( curView );
	}

}

void Camera::SetCameraBounds( sf::Vector2f bounds )
{
	sf::View curView = m_window->getView();
	curView.setSize( bounds );
	m_window->setView( curView );
}

sf::Vector2f Camera::GetCameraBounds()
{
	return m_screenSize * m_zoom;
}