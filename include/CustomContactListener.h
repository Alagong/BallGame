#pragma once
#include <Box2D\box2d.h>
#include "Object.h"
#include "ComponentEngine\CompEvents.h"
#include <iostream>
class CustomContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact)
	{
		Object* a = (Object*)contact->GetFixtureA()->GetUserData();
		Object* b = (Object*)contact->GetFixtureB()->GetUserData();
		
		a->ExecuteEvent( EVENT_STARTEDCOLLIDING, (void*)contact );
		b->ExecuteEvent( EVENT_STARTEDCOLLIDING, (void*)contact );
	}
};