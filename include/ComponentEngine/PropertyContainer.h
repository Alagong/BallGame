//
//	A PropertyContainer is a container of properties and has functions to manipulate those properties
//	for example deleting, adding, changing properties
//	See Property.h
//

#pragma once

#include "ComponentEngine/IProperty.h"
#include "ComponentEngine/Property.h"
#include <iostream>
#include <boost/any.hpp>
class Component;
class PropertyContainer
{
public:
	PropertyContainer() { }
	virtual ~PropertyContainer() { RemoveAllProperties(); }

	bool HasProperty(const std::string& propName);

	template<class T>Property<T> AddProperty(const std::string& propName, const T &defaultValue);
	void AddProperty(IProperty *property);

	template<class T>Property<T> GetProperty(const std::string& propName);
	IProperty *GetIProperty(const std::string& propName);
	
	void RemoveProperty(const std::string& propName, bool postponeDelete = false);
	void RemoveAllProperties();
	
	std::map<std::string, IProperty*> &GetProperties() { return properties; }

	std::vector<IProperty*> &GetNewProperties() { return addedProperties; }
	std::vector<IProperty*> &GetDeletedProperties() { return deletedProperties; }
	
	void UpdateProperties(int deltaTime);

protected:
	void ClearDirtyProperties();
	void ClearAddedProperties();
	void ClearDeletedProperties();

	std::map<std::string, IProperty*> properties;

	std::vector<IProperty*> addedProperties;
	std::vector<IProperty*> deletedProperties;
};


inline bool PropertyContainer::HasProperty(const std::string& propName)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(propName);
	if(it != properties.end())
		return true;
	else
		return false;
}

inline void PropertyContainer::AddProperty(IProperty *property)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(property->GetName());
	if(it == properties.end())
	{
		addedProperties.push_back(property);
		properties[property->GetName()] = property;
	}
}

template<class T>
inline Property<T> PropertyContainer::AddProperty(const std::string& propName, const T &defaultValue)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		Property<T>* property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw "Property already exists, but with another type!";
		return *property;
	}

	Property<T> *property = new Property<T>(propName);
	property->Set(defaultValue);
	addedProperties.push_back(property);
	properties[property->GetName()] = property;

	return *property;
}

template<class T>
inline Property<T> PropertyContainer::GetProperty(const std::string& propName)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		Property<T>* property = dynamic_cast< Property<T>* >(it->second);
		if(!property)
			throw "Tried to get property , but the type was wrong!";
		return *property;
	}
	else
	{
		Property<T> prop = AddProperty<T>(propName,NULL);
		return prop;
	}
}

inline IProperty *PropertyContainer::GetIProperty(const std::string& propName)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		return it->second;
	}
	else
		throw "Unable to get property ";
}

inline void PropertyContainer::RemoveProperty(const std::string& propName, bool postponeDelete)
{
	std::map<std::string, IProperty*>::iterator it = properties.find(propName);
	if(it != properties.end())
	{
		IProperty* property = (*it).second;
		if(postponeDelete)
			deletedProperties.push_back(property);
		else
			delete property;
		properties.erase(it);
	}
}

inline void PropertyContainer::RemoveAllProperties()
{
	std::map<std::string, IProperty*>::iterator it;
	for(it = properties.begin(); it != properties.end(); ++it)
	{
		IProperty* property = (*it).second;
		delete property;
	}
	properties.clear();
	ClearAddedProperties();
	ClearDeletedProperties();
}

inline void PropertyContainer::UpdateProperties(int deltaTime)
{
	//SigUpdateProperties.invoke(deltaTime);

	ClearDirtyProperties();
	ClearAddedProperties();
	ClearDeletedProperties();
}

inline void PropertyContainer::ClearDirtyProperties()
{
	std::map<std::string, IProperty*>::iterator it = properties.begin();
	for(; it != properties.end(); ++it)
	{
		IProperty* property = (*it).second;
		if(property->IsDirty())
		{
			property->ClearDirty();
		}
	}
}

inline void PropertyContainer::ClearAddedProperties()
{
	addedProperties.clear();
}

inline void PropertyContainer::ClearDeletedProperties()
{
	std::vector<IProperty*>::iterator it;
	for(it = deletedProperties.begin(); it != deletedProperties.end(); ++it)
	{
		IProperty* property = (*it);
		delete property;
	}
	deletedProperties.clear();
}