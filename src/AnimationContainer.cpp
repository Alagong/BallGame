#include "AnimationContainer.h"
#include <iostream>
#include <fstream>
#include <json_spirit.h>
#include "Frame.h"
#include "ComponentEngine/CompEvents.h"
#include "Animation.h"
std::map<std::string,int> AnimationContainer::animationNames;

AnimationContainer::AnimationContainer()
{
	AnimationContainer::MapEventsToAnimations();
}
//Call this from somewhere in your code
void AnimationContainer::MapEventsToAnimations()
{
	AnimationContainer::animationNames["Game.Anim.Jump"] = EVENT_JUMPED;
	AnimationContainer::animationNames["Game.Anim.StartMove"] = EVENT_STARTEDMOVING;
	AnimationContainer::animationNames["Game.Anim.Idle"] = EVENT_STARTEDIDLING;
	AnimationContainer::animationNames["Game.Anim.Spawn"] = EVENT_SPAWNED;
	AnimationContainer::animationNames["Game.Anim.Death"] = EVENT_DIED;
	AnimationContainer::animationNames["Game.Anim.DealthDamage"] = EVENT_DEALTHDAMAGE;
	AnimationContainer::animationNames["Game.Anim.Fire"] = EVENT_FIRED;
}

bool AnimationContainer::loadFromFile(std::string &path)
{
	std::ifstream file(path);

	if(!file.is_open())
	{
		return false;
	} else {
		//Parse file
		if(!ParseJson(file,path))
		{
			return false;
		}
	}
	return true;
}

bool AnimationContainer::ParseJson(std::ifstream &file, std::string &path)
{
	json_spirit::Value root;
	try
	{
		json_spirit::read_or_throw(file,root);
	}		
	catch (json_spirit::Error_position &error) {
		std::cout << "Failed to parse animation file" << path << "\n" <<
			"Line : " << error.line_ << "\n" <<
			"Column : " << error.column_ << "\n" <<
			"Reason : " << error.reason_ << std::endl;
		return false;
	}

	json_spirit::Object rootObj = root.get_obj();
	//For every Animation
	for(unsigned int i = 0; i < rootObj.size(); i++)
	{
		json_spirit::Object animation = rootObj.at(i).value_.get_obj();

		std::string animationName = animation[0].value_.get_str();
		//find the enum for the animation name
		std::map<std::string,int>::iterator it;
		it = AnimationContainer::animationNames.find(animationName);
		if(it == AnimationContainer::animationNames.end())
			return false;
		int animEnum = it->second;
		bool isLoopingAnimation = animation[1].value_.get_bool();
		//Frames
		json_spirit::Array frames = animation[2].value_.get_array();

		Animation* newAnim = new Animation();
		newAnim->SetLooping(isLoopingAnimation);
		for(unsigned int i = 0; i < frames.size(); i++)
		{
			json_spirit::Object frame = frames[i].get_obj();
			int posX = 0;
			int posY = 0;
			int frameTime = 100;

			posX = frame[0].value_.get_int();
			posY = frame[1].value_.get_int();
			frameTime = frame[2].value_.get_int();

			Frame *newFrame = new Frame(posX,posY,frameTime);
			newAnim->AddFrame(newFrame);
		}
		animations[animEnum] = newAnim;
	}
	file.close();
	return true;
}

Animation* AnimationContainer::GetAnimation(int animation)
{
	std::map<int,Animation*>::iterator it;
	it = animations.find(animation);
	//If there is no animation
	if(it == animations.end())
	{
		return NULL;
	}
	//Get Frame
	return it->second;
}