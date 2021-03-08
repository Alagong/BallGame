#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
class Object;
class b2Fixture;
class b2Body;
class FixtureBox : public Component
{
public:
	FixtureBox(Entity *entity, const std::string &name);
	virtual ~FixtureBox();

	static Component* Create(Entity* entity, const std::string &name) { return new FixtureBox(entity, name); }

	void Init();
	void Update(int delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	b2Fixture* fixture;
	b2Body* body;

	void OnisSensorChanged(const bool &oldValue, const bool &newValue);
protected:
	Property<float> width;
	Property<float> height;
	Property<float> posX;
	Property<float> posY;
	Property<float> rotation;

	Property<float> collisionWidth;
	Property<float> collisionHeight;
	Property<float> collisionOffsetX;
	Property<float> collisionOffsetY;
	Property<bool> isSensor;
	Property<float> density;
	Property<float> friction;
	Property<bool> parented;
	Property<Object*> parentObject;
	Property<int> parentId;
	Property<int> collisionGroup;
	Property<int> categoryBits;
	Property<int> maskBits;

	Property<b2Fixture**> fixtureBox;
	Property<b2Body**> physBody;

	Object* go;

};