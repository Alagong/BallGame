#pragma once
#include "ComponentEngine/Component.h"
#include "Object.h"
#include <string>
#include <Box2D\Box2D.h>
#include "Waypoint.h"
class TrackTrain : public Component
{
public:
	TrackTrain(Entity *entity, const std::string &name);
	virtual ~TrackTrain();

	static Component* Create(Entity* entity, const std::string &name) { return new TrackTrain(entity, name); }

	void Init();
	void Update(float delta);
	void Draw(sf::RenderWindow& window);
	void ExecuteCommand(int command, void* data = 0);
	void ExecuteEvent(int event, void* data);
private:
	bool compInitialized;
	b2PrismaticJointDef pjd;
	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	b2Body* body;
	Waypoint* nextWaypoint;
	b2Vec2 movingDirection;

	b2Vec2 lastWaypointPos;

	void SetNewWaypoint(int id);
	void OnStartWaypointChanged(const int &oldValue, const int &newValue);
	void OnActivatedChanged(const bool &oldValue, const bool &newValue);
protected:
	Property<int> startWaypointID;
	Property<float> width;
	Property<float> height;

	Property<float> posX;
	Property<float> posY;

	Property<float> rotation;

	Property<float> speed;

	Property<b2Body**> physBody;

	Property<bool> staticObject;
	Property<bool> activated;
	
	Object* go;

};