#include "Components/CameraController.h"
#include "ComponentEngine/CompEvents.h"
#include "Object.h"
#include "Camera.h"
#include <boost/bind.hpp>
CameraController::CameraController(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	posX = go->AddProperty<float>("PosX",0.0f);
	posY = go->AddProperty<float>("PosY",0.0f);

	width = go->AddProperty<float>("Width",0);
	height = go->AddProperty<float>("Height",0);

	cameraID = go->AddProperty<int>("CameraID", -1);
	cameraZoom = go->AddProperty<float>("CameraZoom", 1.0 );
	zoomTime = go->AddProperty<float>("ZoomTime", 0.0 );
}

CameraController::~CameraController()
{

}

void CameraController::Init()
{
	cameraZoom.ValueChanged().connect(boost::bind(&CameraController::OnZoomChanged,this,_1,_2));
}

void CameraController::Update(float delta)
{
	if( cameraID == Camera::Instance()->GetActiveCameraID() )
	{
		Camera::Instance()->SetCenter( sf::Vector2f( posX.Get(), posY.Get() ) );
	}
}

void CameraController::Draw(sf::RenderWindow &window)
{

}

void CameraController::ExecuteCommand(int command, void* data)
{

}

void CameraController::ExecuteEvent(int event, void* data)
{

}

void CameraController::OnZoomChanged( const float &oldValue, const float &newValue )
{
	Camera::Instance()->Zoom( newValue, zoomTime.Get() );
}