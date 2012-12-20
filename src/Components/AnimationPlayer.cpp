#include "Components/AnimationPlayer.h"
#include <iostream>
#include <boost/bind.hpp>
#include "Frame.h"
#include "ComponentEngine/CompEvents.h"
#include "Animation.h"
#include "AnimationHandler.h"
#include "AnimationContainer.h"
AnimationPlayer::AnimationPlayer(Entity *entity, const std::string &name)
	: Component(entity,name), go((Object*)entity)
{
	spriteWidth = go->AddProperty<float>("SpriteWidth",32);
	spriteHeight = go->AddProperty<float>("SpriteHeight",32);

	imagePosX = go->AddProperty<float>("ImagePosX",0);
	imagePosY = go->AddProperty<float>("ImagePosY",0);
	skin = go->AddProperty<int>("Skin",1);
	startAnimation = go->AddProperty<std::string>("StartAnimation","Game.Anim.Idle");


	compInitialized = false;
	frameElapsedTime = 0;
	currentFrameIndex = 0;
	currentAnimationFrames = 0;
	currentAnimation = 0;
}

AnimationPlayer::~AnimationPlayer()
{

}

void AnimationPlayer::Init()
{
	if(!go->HasProperty("Sprite")) return;
	spritePtr = go->GetProperty<sf::Sprite*>("Sprite");
	if(!go->HasProperty("SpriteImage")) return;
	imagePath = go->GetProperty<std::string>("SpriteImage");
	animations = AnimationHandler::Instance()->GetAnimationCont(imagePath.Get());
	if(animations == NULL)
	{
		std::cout << "Could not load animation for : " << imagePath.Get() << std::endl;
		return;
	}
	//Load starting animation
	std::map<std::string,int>::iterator it;
	it = AnimationContainer::animationNames.find(startAnimation.Get());

	if(it == AnimationContainer::animationNames.end())
	{
		currentAnimation = NULL;
		currentFrame = NULL;
	} else {
		
		currentAnimation = animations->GetAnimation(it->second);
		if(currentAnimation)
		{
			currentFrame = currentAnimation->GetFrame(0);
			UpdateSpriteSubRect();
		}
	}

	compInitialized = true;
}

void AnimationPlayer::Update(float delta)
{
	if(compInitialized)
	{
		if(currentAnimation)
		{
			if(frameElapsedTime >= currentFrame->frameTime)
			{
				//Load next frame
				Frame *newFrame = currentAnimation->GetFrame(currentFrameIndex);
				if(newFrame)
				{
					currentFrame = newFrame;
					currentFrameIndex++;
					UpdateSpriteSubRect();
					frameElapsedTime = 0;

				} else {
					//We reached end of animation, start over
					if( currentAnimation->IsLooping() )
					{
						currentFrameIndex = 0;
					} else 
					{
						currentAnimation = NULL;
						currentFrameIndex = 0;
						frameElapsedTime = 0;
					}
				}
			} else 
			{
				frameElapsedTime += delta;
			}
		}
	}
}

void AnimationPlayer::Draw(sf::RenderWindow &window)
{

}

void AnimationPlayer::ExecuteCommand(int command, void* data )
{

}

void AnimationPlayer::ExecuteEvent(int event, void* data)
{
	std::map<int,Animation*>::iterator it;
	Animation* newAnimation = animations->GetAnimation(event);
	if(newAnimation)
	{
		currentAnimation = newAnimation;
		currentFrame = newAnimation->GetFrame(0);
		currentFrameIndex = 0;
	}
}

void AnimationPlayer::UpdateSpriteSubRect()
{
	int sheetPosX = (currentFrame->posX*spriteWidth);
	int sheetPosY = currentFrame->posY*spriteHeight;
	float skinX = sheetPosX+spriteWidth.Get()*skin.Get();
	spritePtr.Get()->setTextureRect( sf::IntRect( skinX, sheetPosY, spriteWidth, spriteHeight ) );
	imagePosX = sheetPosX;
	imagePosY = sheetPosY;
}