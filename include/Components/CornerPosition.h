#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
class Object;
class CornerPosition : public Component
{
public:
	CornerPosition(Entity *entity, const std::string &name);
	virtual ~CornerPosition();

	static Component* Create(Entity* entity, const std::string &name) { return new CornerPosition(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:


protected:
	Property<float> posX;
	Property<float> posY;

	Property<float> cposX;
	Property<float> cposY;

	Property<float> width;
	Property<float> height;
	Object* go;

};