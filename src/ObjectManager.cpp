#include "ObjectManager.h"
#include "Object.h"
#include "Timer.h"
#include "Waypoint.h"
ObjectManager* ObjectManager::objectManagerInstance;
ObjectManager* ObjectManager::Instance()
{
	if( !objectManagerInstance )
		objectManagerInstance = new ObjectManager();

	return objectManagerInstance;
}

ObjectManager::ObjectManager()
{
	fpsTimer = new Timer();
	//What
	std::list<Object*> e;
	objectLists.push_back( e );
	objectLists.push_back( e );
	objectLists.push_back( e );
	objectLists.push_back( e );
	objectLists.push_back( e );
	objectLists.push_back( e );
}

ObjectManager::~ObjectManager()
{
	delete fpsTimer;
}

void ObjectManager::AddObject( Object* obj, Layer layer )
{
	int l = layer;
	if( l < 0 ) 
		l = 0;
	if( l > LAYER_COUNT ) l = LAYER_COUNT - 1;
	objectLists[l].push_back( obj );

}

void ObjectManager::UpdateObjects()
{
	float delta = fpsTimer->GetMilliseconds();
	fpsTimer->Restart();
	for( int i = 0; i < LAYER_COUNT; ++i )
	{
		for( std::list<Object*>::iterator it = objectLists[i].begin(); it != objectLists[i].end(); ++it )
		{
			(*it)->UpdateComponents( delta );
		}
	}

	for( int i = 0; i < LAYER_COUNT; ++i )
	{
		for( std::list<Object*>::iterator it = objectLists[i].begin(); it != objectLists[i].end(); )
		{
			if( (*it)->ShouldBeRemoved() )
			{
				delete *it;
				it = objectLists[i].erase( it );
			} else 
			{
				++it;
			}
		}
	}
}

void ObjectManager::DrawObjects(sf::RenderWindow* window)
{
	for( int i = 0; i < LAYER_COUNT; ++i )
	{
		for( std::list<Object*>::iterator it = objectLists[i].begin(); it != objectLists[i].end(); ++it )
		{
			(*it)->DrawComponents( window );
		}
	}
}

void ObjectManager::InitAllObjects()
{
	for( int i = 0; i < LAYER_COUNT; ++i )
	{
		for( std::list<Object*>::iterator it = objectLists[i].begin(); it != objectLists[i].end(); ++it )
		{
			(*it)->InitComponents();
		}
	}
}

Waypoint* ObjectManager::GetWaypointByID(int id)
{
	for(std::vector<Waypoint*>::iterator it = waypoints.begin(); it != waypoints.end(); it++)
	{
		if((*it)->GetID() == id)
		{
			return (*it);
		}
	}
	return NULL;
}

void ObjectManager::AddWaypoint( Waypoint* wp )
{
	waypoints.push_back( wp );
}

Object* ObjectManager::GetObjectByID(int id)
{
	for( int i = 0; i < LAYER_COUNT; ++i )
	{
		for( std::list<Object*>::iterator it = objectLists[i].begin(); it != objectLists[i].end(); ++it )
		{
			if((*it)->GetID() == id)
			{
				return (*it);
			}
		}
	}
	return NULL;
}