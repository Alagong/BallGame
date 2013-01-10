#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawManager.h"
Camera* Camera::cameraInstance;
Camera* Camera::Instance()
{
	if( !cameraInstance )
		cameraInstance = new Camera();
	return cameraInstance;
}

Camera::Camera()
{
	activeCameraID = 0;
	SetWindowPtr( DrawManager::Instance()->Window() );
	zoom = 1.0f;
	zooming = false;
	zoomTime = 1.0f;
	zoomFrom = zoom;
	zoomTo = zoom;
}

void Camera::Update( float delta )
{
	if( zooming && zoomTime > zoomTimer.GetSeconds() )
	{
		float interpScale = zoomTimer.GetSeconds() / zoomTime;
		float diff = zoomTo - zoomFrom;
		float newZoom = zoomFrom + (diff * interpScale);
		zoom = newZoom;

		sf::View curView = window->getView();
		curView.setSize( screenSize * zoom );
		window->setView( curView );

	} else 
	{
		zoom = zoomTo;
		zooming = false;
	}
}

void Camera::SetWindowPtr( sf::RenderWindow* windowPtr )
{
	this->window = windowPtr;
	sf::View curView = window->getView();
	screenSize = curView.getSize();
}

void Camera::SetCenter( sf::Vector2f center )
{
	this->center = center;
	sf::View curView = window->getView();
	curView.setCenter( center );
	window->setView( curView );
}

void Camera::UpdateWindowView()
{
	sf::View curView = window->getView();
	curView.setCenter( center );
	window->setView( curView );
}

void Camera::Zoom( float scale, float time )
{
	if( time != 0 )
	{
		zoomTimer.Restart();
		zooming = true;
		zoomFrom = zoom;
		zoomTo = scale;
		zoomTime = time;
	} else {
		sf::View curView = window->getView();
		curView.setSize( screenSize * scale );
		window->setView( curView );
	}

}

int Camera::GetActiveCameraID()
{
	return activeCameraID;
}

void Camera::SetActiveCameraID( int ID )
{
	activeCameraID = ID;
}

void Camera::SetCameraBounds( sf::Vector2f bounds )
{
	sf::View curView = window->getView();
	curView.setSize( bounds );
	window->setView( curView );
}


sf::Vector2f Camera::GetCameraBounds()
{
	return screenSize * zoom;
}