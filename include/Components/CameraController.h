#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"

class Object;
class CameraController : public Component
{
public:
	CameraController(Entity *entity, const std::string &name);
	virtual ~CameraController();

	static Component* Create(Entity* entity, const std::string &name) { return new CameraController(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	void OnZoomChanged(const float &oldValue, const float &newValue);
protected:
	Property<float> posX;
	Property<float> posY;
	Property<float> width;
	Property<float> height;
	Property<int> cameraID;
	Property<float> cameraZoom;
	Property<float> zoomTime;
	
	Object* go;

};