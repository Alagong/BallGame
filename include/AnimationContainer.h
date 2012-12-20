#pragma once

#include <map>
#include <vector>
#include <string>

class Animation;
class AnimationContainer
{
private:

	std::map<int,Animation*> animations;
public:
	AnimationContainer();
	static void MapEventsToAnimations();
	static std::map<std::string,int> animationNames; //animation names coresponds to a number which is their position in an ENUM

	bool loadFromFile(std::string &path);

	Animation* GetAnimation(int animation);
private:
	bool ParseJson(std::ifstream &stream, std::string &path);
	bool ParseXml( std::ifstream &stream, std::string &path);
};