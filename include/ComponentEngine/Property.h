#pragma once
#include "ComponentEngine/IProperty.h"
#include <string>
#include <vector>
#include <memory>
#include <boost/signal.hpp>
template<class T>
class PropertyData
{
public:
	T value;
	std::string name;
	bool dirty;
	//CL_Signal_v2<const T&, const T&> valueChanged;
	boost::signal<void(const T&, const T&)> valueChanged;
};

template<class T>
class Property : public IProperty
{
public:
	Property()
	{
	}

	Property(const Property& copy)
	: data(copy.data)
	{
	}

	Property(const std::string &name)
	: data(new PropertyData<T>())
	{	
		data->name = name; 
		data->dirty = false; 
	}

	virtual ~Property() {}

	void Set(const T& value, bool triggerChanged = true) 
	{ 
		if(data->value != value)
		{
			T oldValue = data->value;
			data->value = value; 
			data->dirty = true;
			if(triggerChanged)
				data->valueChanged(oldValue,data->value);
		}
	}
	const T& Get() const { return data->value; }

	virtual const std::string &GetName() const { return data->name; }

	//virtual bool IsNull() const { return data == (PropertyData<T> *) NULL; }

	virtual bool IsDirty() const { return data->dirty; }
	virtual void ClearDirty() { data->dirty = false; }

	//virtual std::string ToString() const { return TypeSerializer::ToString(data->value); }
	//virtual void SetFromString(const T_String &value) { TypeSerializer::FromString(value, data->value); }
	//virtual int GetTypeId() const { return TypeSerializer::GetTypeId(data->value); }

	//CL_Signal_v2<const T&, const T&> &ValueChanged() { return data->valueChanged; }
	boost::signal<void(const T&, const T&)> &ValueChanged() { return data->valueChanged; }

	Property<T> operator= (const Property<T>& rhs);
	Property<T> operator= (const T& rhs);

	Property<T> operator+= (const Property<T>& rhs);
	Property<T> operator+= (const T& rhs);

	Property<T> operator-= (const Property<T>& rhs);
	Property<T> operator-= (const T& rhs);

	bool operator== (const Property<T>& rhs);
	bool operator== (const T& rhs);

	bool operator!= (const Property<T>& rhs);
	bool operator!= (const T& rhs);

	bool operator> (const Property<T>& rhs);
	bool operator> (const T& rhs);

	bool operator< (const Property<T>& rhs);
	bool operator< (const T& rhs);

	operator T() const { return data->value; }

private:
	//CL_SharedPtr< PropertyData<T> > data;
	std::tr1::shared_ptr< PropertyData<T> > data;
};

template<class T>
inline Property<T> Property<T>::operator =(const Property<T> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator =(const T &rhs)
{
	Set(rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const Property<T> &rhs)
{
	Set(data->value + rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const T &rhs)
{
	Set(data->value + rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const Property<T> &rhs)
{
	Set(data->value - rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const T &rhs)
{
	Set(data->value - rhs);
	return *this;
}

template<class T>
inline bool Property<T>::operator ==(const Property<T> &rhs)
{
	return data == rhs.data;
}

template<class T>
inline bool Property<T>::operator ==(const T &rhs)
{
	return (data->value == rhs);
}

template<class T>
inline bool Property<T>::operator !=(const Property<T> &rhs)
{
	return data != rhs.data;
}

template<class T>
inline bool Property<T>::operator !=(const T &rhs)
{
	return (data->value != rhs);
}

template<class T>
inline bool Property<T>::operator >(const Property<T> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class T>
inline bool Property<T>::operator >(const T &rhs)
{
	return (data->value > rhs);
}

template<class T>
inline bool Property<T>::operator <(const Property<T> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class T>
inline bool Property<T>::operator <(const T &rhs)
{
	return (data->value < rhs);
}