//
//	The ComponentRegistrator, a call to Register has to be made from somewhere within the program
//	Registers the components with the factory provided
//	
//#pragma once
#include "ComponentEngine/ComponentFactory.h"

#include "Components/ObjectSprite.h"
#include "Components/AnimationPlayer.h"
#include "Components/BodyDynamic.h"
#include "Components/FixtureBox.h"
#include "Components/BodyStatic.h"
#include "Components/AIController_Walker.h"
#include "Components/FixtureSphere.h"
#include "Components/BallCoreController.h"
#include "Components/PlayerInput.h"
#include "Components/BubbleAbsorbable.h"
class ComponentRegistrator
{
public:
	static void Register(ComponentFactory &factory)
	{
		factory.RegisterComponent("ObjectSprite",&ObjectSprite::Create);
		factory.RegisterComponent("AnimationPlayer",&AnimationPlayer::Create);
		factory.RegisterComponent("BodyDynamic",&BodyDynamic::Create);
		factory.RegisterComponent("FixtureBox",&FixtureBox::Create);
		factory.RegisterComponent("BodyStatic",&BodyStatic::Create);
		factory.RegisterComponent("AIController_Walker",&AIController_Walker::Create);
		factory.RegisterComponent("FixtureSphere",&FixtureSphere::Create);
		factory.RegisterComponent("BallCoreController",&BallCoreController::Create);
		factory.RegisterComponent("PlayerInput",&PlayerInput::Create);
		factory.RegisterComponent("BubbleAbsorbable",&BubbleAbsorbable::Create);
	}
};