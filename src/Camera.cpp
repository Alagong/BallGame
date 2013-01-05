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

void Camera::Zoom( float scale )
{
	sf::View curView = window->getView();
	curView.setSize( screenSize * scale );
	window->setView( curView );
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