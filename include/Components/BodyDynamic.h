//
//	A physics body 
//
#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"

class b2Body;
class Object;
class BodyDynamic : public Component
{
public:
	BodyDynamic(Entity *entity, const std::string &name);
	virtual ~BodyDynamic();

	static Component* Create(Entity* entity, const std::string &name) { return new BodyDynamic(entity, name); }

	void Init();
	void Update(int delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	b2Body* body;
protected:
	Property<float> spriteWidth;
	Property<float> spriteHeight;

	Property<float> posX;
	Property<float> posY;

	Property<float> velocityX;
	Property<float> velocityY;

	Property<float> initialVelX;
	Property<float> initialVelY;
	Property<float> initialAngleVel;

	Property<float> rotation;
	Property<bool> fixedRotation;
	Property<b2Body**> physBody;
	Property<bool> staticObject;

	Object* go;


};