#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	template <class T>
	class ValueList
	{
	public:
		ValueList(){}
		T *value(var value)
		{
			this->_values.append(value);
			return (T*)this;
		}
	protected:
		List<var> _getValues()
		{
			return _values;
		}
	private:
		List<var> _values;
	};

}