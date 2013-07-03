#include "Web.h"
#include "Attr.h"

namespace Web
{

	Attr::Attr(var name, var value)
	{
		this->_name = name;
		this->_value = value;
	}

	Attr::~Attr()
	{
	}

	var Attr::name()
	{
		if(this == NULL)
			return NULL;
		else
			return this->_name;
	}

	Attr *Attr::value(var value)
	{
		if(this == NULL)
			return NULL;
		this->_value = value;
		return this;
	}

	Attr &Attr::operator=(const var &value)
	{
		if(this != NULL)
			this->_value = value;
		return *this;
	}

	var Attr::value()
	{
		if(this == NULL)
			return var();
		else
			return this->_value;
	}

	Attr *Attr::clone()
	{
		Attr *tmp = new Attr(this->_name, this->_value);
		return tmp;
	}
	

	AttrList::AttrList()
	{
	}

	AttrList::~AttrList()
	{
		for(unsigned int i = 0; i < this->_list.size(); i++)
		{
			delete this->_list.at(i);
		}
		this->_list.clear();
	}

	AttrList *AttrList::push(var name, var value)
	{
		this->push(new Attr(name, value));
		return this;
	}

	AttrList *AttrList::push(Attr *attr)
	{
		Attr *tmp = this->find(attr->name());
		if(tmp != NULL)
		{
			tmp->value(attr->value());
			delete attr;
		}
		else
			this->_list.append(attr);
		return this;
	}

	unsigned int AttrList::count()
	{
		return this->_list.size();
	}

	Attr *AttrList::at(unsigned int index)
	{
		if(index >= 0 && index < this->_list.size())
			return this->_list.at(index);
		else 
			return NULL;
	}

	Attr *AttrList::find(var name)
	{
		Attr *tmp;
		for(unsigned int i = 0; i < this->count(); i++)
		{
			tmp = this->at(i);
			if(tmp->name() == name)
			{
				return tmp;
			}
		}
		return NULL;
	}

	Attr *AttrList::find(var name, var value)
	{
		Attr *tmp = this->find(name);
		if(tmp != NULL)
			if(tmp->value() == value)
				return tmp;

		return NULL;
	}

	AttrList *AttrList::clear()
	{
		this->_list.clear();
		return this;
	}

	AttrList *AttrList::clone()
	{
		AttrList *tmp = new AttrList();
		for(unsigned int i = 0; i < this->count(); i++)
		{
			tmp->push(this->at(i)->clone());
		}
		return tmp;
	}

}