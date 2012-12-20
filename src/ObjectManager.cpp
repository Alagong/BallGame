#include "ObjectManager.h"
#include "Object.h"
#include "Timer.h"
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