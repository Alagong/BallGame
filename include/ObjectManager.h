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
class Waypoint;
class ObjectManager
{
private:
	static ObjectManager* objectManagerInstance;
	std::list<Object*> objectList;
	std::vector<Waypoint*> waypoints;
public:
	static ObjectManager* Instance();

	ObjectManager();
	~ObjectManager();

	void AddObject(Object* obj, Layer layer = LAYER_MAIN);
	void InitAllObjects();
	void RemoveFlaggedObjects();
	Object* GetObjectByID( int id );

	Waypoint* GetWaypointByID(int id);
	void AddWaypoint( Waypoint *wp );
	void UpdateObjects( float delta );
	void DrawObjects(sf::RenderWindow* window);

	std::vector< std::list<Object*> > objectLists;
};