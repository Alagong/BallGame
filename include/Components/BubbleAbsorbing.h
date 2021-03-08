#pragma once
#include "ComponentEngine/Component.h"
class Object;

class BubbleAbsorbing : public Component
{
public:
	BubbleAbsorbing(Entity *entity, const std::string &name);
	virtual ~BubbleAbsorbing();

	static Component* Create(Entity* entity, const std::string &name) { return new BubbleAbsorbing(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data);
	void ExecuteEvent(int event, void* data = 0);

private:
	Property< float > spriteRadius;

	Object* coreBubblePtr;
	bool absorbing;

protected:
	Object* go;
};