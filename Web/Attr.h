#pragma once

#include "Web.h"

using namespace std;

namespace Web{
		
	class Attr
	{
	public:
		Attr(var name, var value);
		~Attr();
		var name();
		var value();
		Attr *value(var value);
		Attr *clone();
		Attr &operator=(const var &value);
	private:
		var  _name;
		var _value;
	};
	class AttrList
	{
	public:
		AttrList();
		~AttrList();
		AttrList *push(Attr *attr);
		AttrList *push(var name, var value);
		unsigned int count();
		Attr *at(unsigned int index);
		Attr *find(var name);
		Attr *find(var name, var value);
		AttrList *clear();
		AttrList *clone();
	private:
		List<Attr *> _list;
	};

}