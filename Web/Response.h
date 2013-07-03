#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	class Response
	{
	public:
		Response();
		~Response();
		Response *cookie(string name, var value);
		Attr *cookie(string name);
		var renderCookie();
	private:
		AttrList *_cookies;
	};
}