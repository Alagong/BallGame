#pragma once
#include "ComponentEngine/Component.h"
#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
	class RenderWindow;
}

class Object;
class SphereShape : public Component
{
public:
	SphereShape(Entity *entity, const std::string &name);
	virtual ~SphereShape();

	static Component* Create(Entity* entity, const std::string &name) { return new SphereShape(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow* window);
	void ExecuteCommand(int command, void* data);
	void ExecuteEvent(int event, void* data = 0);

private:
	bool compInitialized;
	
	void OnWidthChanged(const float &oldValue, const float &newValue);
	void OnHeightChanged(const float &oldValue, const float &newValue);

	sf::CircleShape circle;

	float startWidth;
	float startHeight;
protected:
	Object* go;

	Property< float > posX;
	Property< float > posY;
	Property< float > width;
	Property< float > height;
	
	Property< int > sphereColorR;
	Property< int > sphereColorG;
	Property< int > sphereColorB;
	Property< int > sphereColorA;

	Property< float > outlineThickness;
};