#pragma once
#include "ComponentEngine/Component.h"
#include <SFML/Graphics.hpp>
#include <string>
class Object;
class ObjectSprite : public Component
{
public:

	ObjectSprite(Entity *entity, const std::string &name);
	virtual ~ObjectSprite();

	static Component* Create(Entity* entity, const std::string &name) { return new ObjectSprite(entity, name); }

	void Init();
	void Update(int delta);
	void Draw(sf::RenderWindow* window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data) {};

private:

	bool compInitialized;

protected:

	sf::Sprite sprite;
	sf::Texture texture;
	Property<std::string> imagePath; //Path to the sprite image
	Property<int> skin;
	Property<bool> randomSkin;
	Property<int> totalSkins;
	Property<float> posX;
	Property<float> posY;
	Property<float> imagePosX;
	Property<float> imagePosY;
	Property<float> offsetX;
	Property<float> offsetY;
	Property<float> spriteWidth;
	Property<float> spriteHeight;
	Property<float> rotation;
	Property<int> alpha;

	//Sharing properties
	Property<sf::Sprite*> spritePtr;

	Object* go;

};