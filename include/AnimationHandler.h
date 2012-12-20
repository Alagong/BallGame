#pragma once

#include <string>
#include <map>

class AnimationContainer;
class AnimationHandler
{
public:
	static AnimationHandler* Instance();
	AnimationHandler();

	AnimationContainer* GetAnimationCont(std::string spriteSheet);
private:
	std::map<std::string,AnimationContainer*> spriteSheetAnimations;

	std::string RemoveExtention(std::string &filePath);

	static AnimationHandler* animationHandlerInstance;
};