#include "Web.h"
#include "Var.h"

namespace Web
{
	using namespace Utility;

	string var::toS()
	{
		string out = "";
		switch(this->_type)
		{
		case TYPE_UNDEFINED:
			out = "";
			break;
		case TYPE_CHAR:
			out = *(char *)this->_value;
			break;
		case TYPE_INT:
			out = intToString(*(int *)this->_value);
			break;
		case TYPE_DOUBLE:
			out = doubleToString(*(double *)this->_value);
			break;
		case TYPE_STRING:
			out = *(string *)this->_value;
			break;
		}
		return out;
	}
	const char* var::toC()
	{
		return this->toS().c_str();
	}

}