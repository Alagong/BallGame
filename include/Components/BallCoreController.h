#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
class Object;
class b2Fixture;
class b2Body;
class BallCoreController : public Component
{
public:
	BallCoreController(Entity *entity, const std::string &name);
	virtual ~BallCoreController();

	static Component* Create(Entity* entity, const std::string &name) { return new BallCoreController(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	b2Body* body;
	int movingDirection[4];

	bool absorbing;
	bool jumping;
	void SplitBubble();
	void OnWidthChanged(const float &oldValue, const float &newValue);

protected:
	Property<float> posX;
	Property<float> posY;
	Property<float> spriteRadius;
	Property<float> height;
	Property<b2Body**> physBody;

	Property<float> cameraZoom;

	Object* go;

};