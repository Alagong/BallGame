#include "ObjectTemplateManager.h"
#include "Object.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include "ComponentEngine/ComponentFactory.h"
using namespace boost::filesystem;
using boost::any_cast;
ObjectTemplate::ObjectTemplate()
{

}

void ObjectTemplate::AddComponent(std::string compName)
{
	m_componentNames.push_back(compName);
}

std::vector<std::string> ObjectTemplate::GetComponentNames()
{
	return m_componentNames;
}

template<class T>
inline void ObjectTemplate::AddProperty(const std::string& propName, const T &value)
{
	m_changedProperties[propName] = value;
}

std::map<std::string, boost::any>& ObjectTemplate::GetProperties()
{
	return m_changedProperties;
}

ObjectTemplateManager* ObjectTemplateManager::objTemplateManagerInstance;
ObjectTemplateManager* ObjectTemplateManager::Instance()
{
	if( !objTemplateManagerInstance )
		objTemplateManagerInstance = new ObjectTemplateManager();
	return objTemplateManagerInstance;
}

ObjectTemplateManager::ObjectTemplateManager() 
{
}

Object* ObjectTemplateManager::Create(std::string name)
{
	ObjectTemplate* objTemplate = NULL;
	objTemplate = GetTemplate(name);

	if(objTemplate == NULL)
	{
		std::cout << "Couldn't find template for object: " << name << std::endl;
		return NULL;
	}

	Object* newObj = CreateFromTemplate(objTemplate);

	if( !newObj )
		std::cout << "Couldn't create object: " << name << std::endl;
	return newObj;
}

Object* ObjectTemplateManager::CreateFromTemplate(ObjectTemplate* objTemplate)
{
	//Create a new object out of the template we found
	Object *newObj = new Object( *ComponentFactory::Instance() );
	newObj->SetName(objTemplate->GetName());
	//Get which components the template has
	//These is stored as a vector of strings in the templated object
	std::vector<std::string> componentNames = objTemplate->GetComponentNames();
	std::vector<std::string>::iterator it2;
	for(it2 = componentNames.begin(); it2 != componentNames.end(); ++it2)
	{
		std::string& name = *it2;
		newObj->AddComponent(name);
	}
	//Get which properties should be changed after the components have been added
	//These change the component's default values
	//These are stored in a map where the key is a string and the value is a boost::any
	std::map<std::string, boost::any> properties = objTemplate->GetProperties();
	std::map<std::string, boost::any>::iterator it3;
	for(it3 = properties.begin(); it3 != properties.end(); ++it3)
	{
		if(is_float(it3->second))
		{
			newObj->GetProperty<float>(it3->first) = any_cast<float>(it3->second);
		} else if(is_int(it3->second))
		{
			newObj->GetProperty<int>(it3->first) = any_cast<int>(it3->second);
		} else if(is_string(it3->second))
		{
			newObj->GetProperty<std::string>(it3->first) = any_cast<std::string>(it3->second);
		} else if(is_bool(it3->second))
		{
			newObj->GetProperty<bool>(it3->first) = any_cast<bool>(it3->second);
		}
	}
	return newObj;
}

ObjectTemplate* ObjectTemplateManager::GetTemplate(std::string name)
{
	std::map<std::string,ObjectTemplate*>::iterator it = templates.find(name);
	if(it != templates.end())
	{
		//Found template
		return it->second;
	}
	return NULL;
}

bool ObjectTemplateManager::Add(ObjectTemplate *obj)
{
	std::pair<std::string,ObjectTemplate*> p(obj->GetName(),obj);
	templates.insert(p);
	return true;
}

bool ObjectTemplateManager::is_int(const boost::any & operand)
{
	return operand.type() == typeid(int);
}
bool ObjectTemplateManager::is_float(const boost::any & operand)
{
	return operand.type() == typeid(float);
}
bool ObjectTemplateManager::is_string(const boost::any & operand)
{
	return (bool)any_cast<std::string>(&operand);
}
bool ObjectTemplateManager::is_bool(const boost::any & operand)
{
	return any_cast<bool>(&operand);
}

void ObjectTemplateManager::LoadObjects(std::string rootFolder)
{
	if(exists(rootFolder))
	{
		directory_iterator end_itr;
		
		for ( directory_iterator itr( rootFolder ); itr != end_itr; ++itr )
		{
			if ( is_directory( *itr ) )
			{
				LoadObjects(itr->path().string()); //Load objects in folder
			} else {
				std::string fileExtention = itr->path().extension().string();
				if(fileExtention.compare(".json") != 0) continue; //Skip this file

				ObjectTemplate *obj = new ObjectTemplate();
				std::ifstream file(itr->path().string());
				if(!file.is_open())
				{
					std::cout << "Failed to open file\n";
					return;
				}
				
				json_spirit::Value root;
				try
				{
					json_spirit::read_or_throw(file,root);
				} catch (json_spirit::Error_position error) {
					std::cout << "Failed to parse file" << itr->path().string() << "\n" <<
						"Line : " << error.line_ << "\n" <<
						"Column : " << error.column_ << "\n" <<
						"Reason : " << error.reason_ << std::endl;
				}

				json_spirit::Object rootObj = root.get_obj();
				
				std::string objName = rootObj[0].value_.get_str();
				std::cout << "Loading object: " << objName << std::endl;
				obj->SetName(objName);
				LoadComponents(rootObj[1].value_.get_obj(), obj);
				Add(obj);

				file.close();
			}
		}
	}
}

void ObjectTemplateManager::LoadComponents(json_spirit::Object &components, ObjectTemplate* obj)
{
	for(json_spirit::Object::iterator it = components.begin(); it != components.end(); it++)
	{
		obj->AddComponent( (*it).name_ );

		if ( !(*it).value_.is_null() ) //Has properties
		{
			json_spirit::Object properties = (*it).value_.get_obj();
			LoadProperties( properties, obj );
		}
	}
}

void ObjectTemplateManager::LoadProperties( json_spirit::Object &properties, ObjectTemplate* obj )
{
	for(unsigned int i = 0; i < properties.size(); i++)
	{
		std::string propertyName = properties.at(i).name_;
		json_spirit::Value_type type = properties.at(i).value_.type();
					
		switch(type)
		{
			case json_spirit::int_type:
				{
					obj->AddProperty<int>(propertyName, properties.at(i).value_.get_int());
					break;
				}
			case json_spirit::real_type:
				{
					obj->AddProperty<float>(propertyName, properties.at(i).value_.get_real());
					break;
				}
			case json_spirit::bool_type:
				{
					obj->AddProperty<bool>(propertyName, properties.at(i).value_.get_bool());
					break;
				}
			case json_spirit::str_type:
				{
					obj->AddProperty<std::string>(propertyName, properties.at(i).value_.get_str());
					break;
				}
			default:
				break;
		}
	}
}