#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>
Camera* Camera::cameraInstance;
Camera* Camera::Instance()
{
	if( !cameraInstance )
		cameraInstance = new Camera();
	return cameraInstance;
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
	UpdateWindowView();
}

void Camera::UpdateWindowView()
{
	sf::View curView = window->getView();
	curView.setCenter( center );
	curView.setSize( screenSize * zoom );
	window->setView( curView );
}