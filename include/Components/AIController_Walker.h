#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"

class Timer;
class b2Body;
class b2Fixture;
class Object;
class AIController_Walker : public Component
{
public:
	AIController_Walker(Entity *entity, const std::string &name);
	virtual ~AIController_Walker();

	static Component* Create(Entity* entity, const std::string &name) { return new AIController_Walker(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:

	bool tilted;
	bool groundFound;
	Timer* tiltedTimer;

	bool findGround();

protected:
	Property<float> posX;
	Property<float> posY;
	Property<float> spriteWidth;
	Property<float> spriteHeight;
	Property<b2Fixture**> fixtureBox;
	Property<b2Body**> physBody;
	
	b2Body *body;

	Object* go;

};