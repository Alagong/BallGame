//
//	Used to load and store predefined objects in json files stored in resources/data/objects
//
#pragma once
#include <string>
#include <map>
#include <boost/any.hpp>
#include "json_spirit.h"
#include <vector>
class ComponentFactory;
class Object;


class ObjectTemplate
{
public:
	ObjectTemplate();
	void SetName(std::string objectName) {m_objectName = objectName;}
	std::string GetName() {return m_objectName;}

	void AddComponent(std::string compName);
	std::vector<std::string> GetComponentNames();

	template<class T> void AddProperty(const std::string& propName, const T &value);
	std::map<std::string, boost::any> &GetProperties();
private:
	std::string m_objectName;
	std::vector<std::string> m_componentNames;
	std::map<std::string, boost::any> m_changedProperties;
};


class ObjectTemplateManager
{
public:
	static ObjectTemplateManager* Instance();
	ObjectTemplateManager();
	ObjectTemplate* GetTemplate(std::string name);

	Object* Create(std::string name);
	Object* CreateFromTemplate(ObjectTemplate* objTemplate);
	
	bool Add(ObjectTemplate* obj);
	void LoadObjects(std::string rootFolder);
	
	void LoadComponents( json_spirit::Object &components, ObjectTemplate* obj );
	void LoadProperties( json_spirit::Object &properties, ObjectTemplate* obj );
private:
	bool is_int(const boost::any & operand);
	bool is_float(const boost::any & operand);
	bool is_string(const boost::any & operand);
	bool is_bool(const boost::any & operand);

	std::map<std::string,ObjectTemplate*> templates;

	static ObjectTemplateManager* objTemplateManagerInstance;
};