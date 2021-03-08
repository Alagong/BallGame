#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
class Object;
class b2Fixture;
class b2Body;
class PlayerInput : public Component
{
public:
	PlayerInput(Entity *entity, const std::string &name);
	virtual ~PlayerInput();

	static Component* Create(Entity* entity, const std::string &name) { return new PlayerInput(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	bool jumpPressed;
protected:
	Object* go;

};