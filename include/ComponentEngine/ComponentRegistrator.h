//
//	The ComponentRegistrator, a call to Register has to be made from somewhere within the program
//	Registers the components with the factory provided
//	
//#pragma once
#include "ComponentEngine/ComponentFactory.h"

#include "Components/ObjectSprite.h"
#include "Components/AnimationPlayer.h"
#include "Components/BodyDynamic.h"
class ComponentRegistrator
{
public:
	static void Register(ComponentFactory &factory)
	{
		factory.RegisterComponent("ObjectSprite",&ObjectSprite::Create);
		factory.RegisterComponent("AnimationPlayer",&AnimationPlayer::Create);
		factory.RegisterComponent("BodyDynamic",&BodyDynamic::Create);
	}
};