#include "MapLoader.h"
#include <json_spirit.h>
#include <boost/filesystem.hpp>
#include <string>
#include "Object.h"
#include "Waypoint.h"
#include "ObjectManager.h"
#include "ObjectTemplateManager.h"
using namespace boost::filesystem;

MapLoader::MapLoader()
{
}

void MapLoader::LoadMap(std::string &mapFolderPath)
{
	std::string folder(mapFolderPath);
	if(exists(folder))
	{
		directory_iterator end_itr;
		
		for ( directory_iterator itr( folder ); itr != end_itr; ++itr )
		{
			if ( is_directory( *itr ) )
			{
				//std::string path = itr->path().string();

			} else {
				std::string path = itr->path().string();
				std::cout << itr->path() << std::endl;
				std::ifstream file(path);
				if(!file.is_open())
				{
					std::cout << "Failed to open file: " << itr->path() << std::endl;;
					continue;
				}
			
				json_spirit::Value root;
				try
				{
					json_spirit::read_or_throw(file,root);
				}
				
				catch (json_spirit::Error_position error) {
					std::cout << "Failed to parse file" << itr->path().string() << "\n" <<
						"Line : " << error.line_ << "\n" <<
						"Column : " << error.column_ << "\n" <<
						"Reason : " << error.reason_ << std::endl;

				}
				
				

				json_spirit::Object rootObj = root.get_obj();

				for(unsigned int i = 0; i < rootObj.size(); i++)
				{

					json_spirit::Object gameObject = rootObj[i].value_.get_obj();

					std::string keyName = rootObj[i].name_;

					if(keyName.compare("Waypoint") == 0)
					{
						int waypointID = gameObject[0].value_.get_int();
						float waypointPosX = gameObject[1].value_.get_real();
						float waypointPosY = gameObject[2].value_.get_real();
						int waypointNextID = 0;
						float newSpeed = 0;
						bool altWaypoint = false;
						int altWaypointID = 0;

						int size = gameObject.size();

						if(size > 3 && gameObject[3].value_.type() == json_spirit::int_type)
							waypointNextID = gameObject[3].value_.get_int();

						if(size > 4 && gameObject[4].value_.type() == json_spirit::real_type)
							newSpeed = gameObject[4].value_.get_real();

						if(size > 5 && gameObject[5].value_.type() == json_spirit::bool_type)
							altWaypoint = gameObject[5].value_.get_bool();

						if(size > 6 && gameObject[6].value_.type() == json_spirit::int_type)
							altWaypointID = gameObject[6].value_.get_int();


						ObjectManager::Instance()->AddWaypoint(new Waypoint(waypointID, waypointPosX, waypointPosY,
														waypointNextID, newSpeed, altWaypoint, altWaypointID));
					} else if(keyName.compare("Object") == 0)
					{
						int o = 0;

						std::string objName = gameObject[0].value_.get_str();
						Object* newObj = ObjectTemplateManager::Instance()->Create(objName);

						keyName = gameObject[1].name_;
						if(keyName.compare("ExtraComponents") == 0)
						{
							json_spirit::Array strComponents = gameObject[1+o].value_.get_array();
			
							for(json_spirit::Array::iterator it = strComponents.begin();it != strComponents.end(); it++)
							{
								std::string componentName = (*it).get_str();
								newObj->AddComponent(componentName);
							}
							o = 1;
						}
						int objectID = gameObject[1+o].value_.get_int();
						newObj->SetID(objectID);

						for(unsigned int j = 2+o; j < gameObject.size(); j++)
						{
							std::string propertyName = gameObject.at(j).name_;
							if(!newObj->HasProperty(propertyName))
							{
								continue;
							}
							json_spirit::Value_type type = gameObject.at(j).value_.type();
					
							switch(type)
							{
								case json_spirit::int_type:
									{
										newObj->GetProperty<int>(propertyName).Set(gameObject.at(j).value_.get_int());
										break;
									}
								case json_spirit::real_type:
									{
										newObj->GetProperty<float>(propertyName).Set(gameObject.at(j).value_.get_real());
										break;
									}
								case json_spirit::bool_type:
									{
										newObj->GetProperty<bool>(propertyName).Set(gameObject.at(j).value_.get_bool());
										break;
									}
								case json_spirit::str_type:
									{
										newObj->GetProperty<std::string>(propertyName).Set(gameObject.at(j).value_.get_str());
										break;
									}
								default:
									break;
							}

						}
						ObjectManager::Instance()->AddObject( newObj );

						} else {
							continue;
						}

					}
				file.close();
			}
		}
	}
}