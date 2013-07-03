#include "Web.h"
#include "Request.h"

namespace Web
{
	using namespace Utility;

	static const char HttpVarSeparator[] = {
		'=',
		'=',
		'=',
		'='
	};
	static const char HttpVarTerminator[] = {
		'&',
		'&',
		';',
		'\n'
	};

	var file;

	var getFile()
	{
		return file;
	}

	HttpVar::~HttpVar()
	{
	}
	HttpVar::HttpVar(var name, var value, HttpVarType type)
	{
		this->_name = name;
		this->_value = value;
		this->_type = type;
	}
	var HttpVar::name()
	{
		if(this == NULL)
			return "";
		return this->_name;
	}
	var HttpVar::value()
	{
		if(this == NULL)
			return "";
		return this->_value;
	}
	HttpVarType HttpVar::type()
	{
		return this->_type;
	}

	Request::Request(char **env)
	{
		var currentEnv, key, value;
		int i = 0;
		while(*env != 0)
		{
			this->_splitVars(*env, ENV);
			env++;
		}
		this->_method = METHOD_UNDEFINED;
		var method = "";
		var queryString = this->getEnv("QUERY_STRING")->value();
		var cookieString = this->getEnv("HTTP_COOKIE")->value();
		if( (method = this->getEnv("REQUEST_METHOD")->value()) != "")
		{
			if(method == "GET")
			{
				this->_method = METHOD_GET;
			}
			else if(method == "POST")
			{
				this->_method = METHOD_POST;


				const char * cl = getenv("CONTENT_LENGTH");
				if(cl != NULL)
				{
				
					const int ReadBufferSize = 4 * 1024;

					const int post_len = strtol(cl, NULL, 10);
					
					static char *stdin_data;

					stdin_data = (char *)malloc((post_len+1) * sizeof(char));
             		fread(stdin_data, post_len, 1, stdin);

					stdin_data[post_len] = '\0';
					this->_splitVars(stdin_data, POST);
				}

			}
		}
		this->_splitVars(queryString, GET);
		this->_splitVars(cookieString, COOKIE);
	}
	Request::~Request()
	{
		for(unsigned int i = 0; i < this->_vars.size(); i++)
		{
			delete this->_vars[i];
		}
		this->_vars.clear();
	}
	var Request::envDebug()
	{
		Tag *envTag = new Tag(DIV);
		envTag->addClass("debug-box");
		for(unsigned i = 0; i < this->_vars.size(); i++)
		{
			if(this->_vars[i]->type() == ENV)
			{
				(new Tag(P))->append(
					(new Tag(SPAN))->html(this->_vars[i]->name())->addClass("debug-title")
				)->append(
					(new Tag(SPAN))->html(" = ")	
				)->append(
					(new Tag(SPAN))->html(this->_vars[i]->value())->addClass("debug-value")
				)->appendTo(envTag);
			}
		}
		Tag debug_container = Tag(DIV);
		debug_container.addClass("debug-container");
		debug_container.append(envTag);

		return debug_container.html();
	}

	HttpVar *Request::getEnv(var name)
	{
		return this->getVar(name, ENV);	
	}
	HttpVar *Request::getVar(var name, HttpVarType type)
	{
		for(unsigned i = 0; i < this->_vars.size(); i++)
		{
			if(this->_vars[i]->type() == type && this->_vars[i]->name() == name)
				return this->_vars[i];
		}
		return NULL;
	}
	var Request::post(var name)
	{
		return this->getVar(name,POST)->value();
	}
	var Request::get(var name)
	{
		return this->getVar(name,GET)->value();
	}

	var Request::httpVarDebug()
	{
		Tag *envTag = new Tag(DIV);
		envTag->addClass("debug-box");
		for(unsigned i = 0; i < this->_vars.size(); i++)
		{
			if(this->_vars[i]->type() != ENV)
			{
				(new Tag(P))->append(
					(new Tag(SPAN))->html(this->_vars[i]->name())->addClass("debug-title")
				)->append(
					(new Tag(SPAN))->html(" = ")	
				)->append(
					(new Tag(SPAN))->html(this->_vars[i]->value())->addClass("debug-value")
				)->appendTo(envTag);
			}
		}
		Tag debug_container = Tag(DIV);
		debug_container.addClass("debug-container");
		debug_container.append(envTag);

		var html = debug_container.html();

		return html;
	}
	Method Request::method()
	{
		return this->_method;
	}
	bool Request::_splitVars(var text,HttpVarType type)
	{
		int from = 0;
		int to = 0;
		int can = true;
		if(text != "")
		{
			while(can)
			{
				to = text.find(HttpVarTerminator[type],from + 1);

				if(to<0)
				{
					this->_createVar(text.substr(from),type);
					can = false;
				}
				else
					this->_createVar(text.substr(from,to-from),type);
				from = text.find(HttpVarTerminator[type],from + 1) + 1;
				if(from<=0)
					can = false;
			}
		}
		return true;
	}
	bool Request::_createVar(var text,HttpVarType type)
	{
		var name = "";
		var value = "";
		int ugual = text.find(HttpVarSeparator[type]);
		if(ugual <= 0)
    		return false;
		name = text.substr(0,ugual);
		value = urlDecode(text.substr(ugual + 1).toS());
		this->_vars.push_back(new HttpVar(name, value, type));
		return true;
	}
}