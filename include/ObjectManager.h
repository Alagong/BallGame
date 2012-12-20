#pragma once
#include <list>
#include <vector>
enum Layer
{
	LAYER_BACKGROUND,
	LAYER_BACKGROUND_DETAIL,
	LAYER_MAIN,
	LAYER_MAIN_DETAIL,
	LAYER_FOREGROUND,
	LAYER_FOREGROUND_DETAIL,

	LAYER_COUNT
};

namespace sf
{
	class RenderWindow;
}

class Object;
class Timer;
class ObjectManager
{
private:
	static ObjectManager* objectManagerInstance;
	std::list<Object*> objectList;

	Timer* fpsTimer;
public:
	static ObjectManager* Instance();

	ObjectManager();
	~ObjectManager();
	/*
	**	Add a new created object to the list
	*/
	void AddObject(Object* obj, Layer layer = LAYER_MAIN);
	/*
	**	Check objects to see if their removal flag is set to true and remove them
	*/
	void RemoveFlaggedObjects();

	void UpdateObjects();
	void DrawObjects(sf::RenderWindow* window);

	std::vector< std::list<Object*> > objectLists;
};