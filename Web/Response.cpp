#include "Web.h"
#include "Response.h"

namespace Web
{
	Response::Response()
	{
		this->_cookies = new AttrList();
	}
	Response::~Response()
	{
		delete this->_cookies;
	}
	Response *Response::cookie(string name, var value)
	{
		Attr *tmp;
		if((tmp = this->cookie(name)) == NULL)
		{
			this->_cookies->push(new Attr(name, value));
		}
		else
		{
			tmp->value(value);
		}
		return this;
	}
	Attr *Response::cookie(string name)
	{
		for(unsigned int i = 0; i < this->_cookies->count(); i++)
		{
			if(this->_cookies->at(i)->name() == name)
			{
				return this->_cookies->at(i);
			}
		}
		return NULL;
	}
	var Response::renderCookie()
	{
		var render = "";
		for(unsigned int i = 0; i < this->_cookies->count(); i++)
		{
			render = render + "Set-Cookie: " + this->_cookies->at(i)->name() + "=" + this->_cookies->at(i)->value() + "\n";
		}
		return render;
	}
}