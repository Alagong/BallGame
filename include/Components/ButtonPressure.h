#pragma once
#include "ComponentEngine/Component.h"
class Object;
class b2Body;
class ButtonPressure : public Component
{
public:
	ButtonPressure(Entity *entity, const std::string &name);
	virtual ~ButtonPressure();

	static Component* Create(Entity* entity, const std::string &name) { return new ButtonPressure(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data);
	void ExecuteEvent(int event, void* data = 0);

private:
	
	float maxHeightPos;
	float activatePos;
	float lockedPosX;

	bool activated;

protected:

	Property<float> posY;
	Property<float> posX;
	Property<float> height;
	Property<int> objectToActivate;
	Property<float> gravityScale;

	Property<b2Body**> physBody;

	b2Body* body;

	Object* go;
};