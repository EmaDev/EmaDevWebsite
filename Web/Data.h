#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	class Data
	{
	public:
		Data(char day, char month, short year)
		{
			this->_day = day;
			this->_month = month;
			this->_year =  year;
		}
	private:
		char _month;
		char _day;
		short _year;
	};
}