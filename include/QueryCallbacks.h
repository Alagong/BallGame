#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <vector>
class Object;
class QueryObjectsAABB : public b2QueryCallback
{
public:
	virtual bool ReportFixture(b2Fixture* fixture);
	std::vector<Object*> objects;
	std::vector<b2Fixture*> fixtures;
};