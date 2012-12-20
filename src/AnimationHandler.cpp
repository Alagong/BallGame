#include "AnimationHandler.h"
#include "AnimationContainer.h"
#include <iostream>

AnimationHandler* AnimationHandler::animationHandlerInstance;
AnimationHandler* AnimationHandler::Instance()
{
	if( !animationHandlerInstance )
		animationHandlerInstance = new AnimationHandler();
	return animationHandlerInstance;
}
AnimationHandler::AnimationHandler()
{

}

AnimationContainer* AnimationHandler::GetAnimationCont(std::string spriteSheet)
{

	std::map<std::string, AnimationContainer*>::iterator it;
	it = spriteSheetAnimations.find(spriteSheet);

	//Remove extention and swap with anim
	std::string animFile(spriteSheet);
	animFile = RemoveExtention(animFile);
	animFile.append(".anim");
	if(it == spriteSheetAnimations.end())
	{
		//Sprite sheet animation not found, try to load it
		AnimationContainer* cont = new AnimationContainer();
		if(cont->loadFromFile(animFile))
		{
			spriteSheetAnimations[spriteSheet] = cont;
			return cont;
		}
	} else {
		//Sprite sheet exists
		return it->second;
	}

	return NULL; //I CAUNT DU ET CAPTAIN, AI DUNT HAVE TE PUWER!
}

std::string AnimationHandler::RemoveExtention(std::string &filePath)
{
	size_t pos = filePath.rfind(".");
    if(pos == std::string::npos)  //No extension.
        return filePath;

    if(pos == 0)    //. is at the front. Not an extension.
        return filePath;

	return filePath.substr(0, pos);
}