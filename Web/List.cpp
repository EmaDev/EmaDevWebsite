#include "Web.h"
#include "List.h"

namespace Web
{
	KeyValue::KeyValue(int null)
	{
	}
	KeyValue::KeyValue(var key, var value)
	{
		this->_key = key;
		this->_value = value;
	}
	KeyValue::KeyValue(const KeyValue& kv)
	{
		this->_key = kv._key;
		this->_value = kv._value;
	}
	var KeyValue::value()
	{
		return this->_value;
	}
	var KeyValue::key()
	{
		return this->_key;
	}

	bool Dictionary::add(var key, var value)
	{
		return this->add(KeyValue(key, value));
	}
	bool Dictionary::add(KeyValue& kv)
	{
		if(this->exist(kv.key()))
			return false;
		this->append(kv);
		return true;
	}
	var Dictionary::find(var key)
	{
		for(unsigned i = 0; i < this->size(); i++)
		{
			if(this->at(i).key() == key)
				return this->at(i).value();
		}
		return NULL;
	}
	bool Dictionary::exist(var key)
	{
		return this->find(key) != NULL;
	}
	var& Dictionary::operator [] (const var& name)
	{
		return this->find(name);
	}
}