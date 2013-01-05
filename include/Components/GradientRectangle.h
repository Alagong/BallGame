#pragma once
#include "ComponentEngine/Component.h"
#include "defines.h"
#include <SFML/Graphics/Vertex.hpp>

namespace sf
{
	class RenderWindow;
};

class Object;
class GradientRectangle : public Component
{
public:
	GradientRectangle(Entity *entity, const std::string &name);
	virtual ~GradientRectangle();

	static Component* Create(Entity* entity, const std::string &name) { return new GradientRectangle(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow* window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	void OnZoomChanged(const float &oldValue, const float &newValue);

	sf::Vertex rectangle[4];
	sf::Vertex lines[5];
protected:
	Property<float> posX;
	Property<float> posY;
	Property<float> width;
	Property<float> height;

	Property<int> gradientDirection; //Up down left right
	
	Property<int> gradientColorAR;
	Property<int> gradientColorAG;
	Property<int> gradientColorAB;

	Property<int> gradientColorBR;
	Property<int> gradientColorBG;
	Property<int> gradientColorBB;
	
	Object* go;

};