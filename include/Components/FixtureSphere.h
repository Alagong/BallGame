#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
class Object;
class b2Fixture;
class b2Body;
class FixtureSphere : public Component
{
public:
	FixtureSphere(Entity *entity, const std::string &name);
	virtual ~FixtureSphere();

	static Component* Create(Entity* entity, const std::string &name) { return new FixtureSphere(entity, name); }

	void Init();
	void Update(int delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	b2Fixture* fixture;
	b2Body* body;
	
	void CreateFixture();

	void OnisSensorChanged(const bool &oldValue, const bool &newValue);
	void OnRadiusChanged(const float &oldValue, const float &newValue);
protected:
	Property<float> spriteRadius;
	Property<float> posX;
	Property<float> posY;
	Property<float> rotation;

	Property<float> collisionRadius;
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