#include "QueryCallbacks.h"
#include "Object.h"
#include <iostream>
bool QueryObjectsAABB::ReportFixture( b2Fixture* fixture )
{
	fixtures.push_back( fixture );
	return true;
}