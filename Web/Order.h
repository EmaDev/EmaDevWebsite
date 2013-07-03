#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	enum ORDER_TYPE { ASC, DESC };
	template <class T>
	class Order
	{
	public:
		Order(){}
		T *order(var value, ORDER_TYPE order)
		{
			if(order == ASC)
			{
				value+= " ASC";
			}
			else
			{
				value+= " DESC";
			}
			return this->order(value);
		}
		T *order(var value)
		{
			this->_values.append(value);
			return (T*)this;
		}
	protected:
		List<var> _getOrder()
		{
			return _values;
		}
	private:
		List<var> _values;
	};

}