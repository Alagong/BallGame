#pragma once
#include "ComponentEngine/Component.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

class Animation;
struct Frame;
class AnimationContainer;
class AnimationPlayer : public Component
{
public:
	AnimationPlayer(Entity *entity, const std::string &name);
	virtual ~AnimationPlayer();

	static Component* Create(Entity* entity, const std::string &name) { return new AnimationPlayer(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data);
	void ExecuteEvent(int event, void* data = 0);

private:
	bool compInitialized;

	AnimationContainer* animations;
	Animation *currentAnimation;
	int frameElapsedTime;
	Frame* currentFrame;
	int currentFrameIndex;
	int currentAnimationFrames;

	std::vector<int> hasAnimations;

	void UpdateSpriteSubRect();
protected:
	Object* go;
	Property<sf::Sprite*> spritePtr;
	Property<std::string> imagePath;
	Property<int> skin;
	Property<std::string> startAnimation;
	Property<float> spriteWidth;
	Property<float> spriteHeight;

	Property<float> imagePosX;
	Property<float> imagePosY;
};