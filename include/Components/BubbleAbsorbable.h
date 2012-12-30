#pragma once
#include "ComponentEngine/Component.h"
class Object;

class BubbleAbsorbable : public Component
{
public:
	BubbleAbsorbable(Entity *entity, const std::string &name);
	virtual ~BubbleAbsorbable();

	static Component* Create(Entity* entity, const std::string &name) { return new BubbleAbsorbable(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data);
	void ExecuteEvent(int event, void* data = 0);

private:
	bool compInitialized;

	Property< float > posX;
	Property< float > posY;
	Property< float > spriteRadius;

protected:
	Object* go;
};