#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#include "Var.h"
#include "List.h"
#include "Table.h"
#include "Condition.h"
#include "SqlValue.h"
#include "Order.h"
#include "Query.h"
#include "Sql.h"
#include "Attr.h"
#include "Tag.h"
#include "Dom.h"
#include "Request.h"
#include "Response.h"
#include "Server.h"


using namespace std;

namespace Web
{
	namespace Utility
	{
	
		string intToString(int _int);
		string doubleToString(double _double);
		int stringToInt(string _string);
		double stringToDouble(string _string);
		string stringClone(string orig);
		string urlDecode(string &src);
		void replaceAll(string& str, const string& from, const string& to);
	}
}