#pragma once

#include "Web.h"

using namespace std;


namespace Web
{
	var getFile();

	enum HttpVarType { POST, GET, COOKIE, ENV };
	class HttpVar
	{
	public:
		HttpVar(var name, var value, HttpVarType type);
		~HttpVar();
		var name();
		var value();
		HttpVarType type();
	private:
		var _name;
		var _value;
		HttpVarType _type;
	};

	enum Method { METHOD_UNDEFINED, METHOD_GET, METHOD_POST };

	class Request
	{
	public:
		Request(char **env);
		~Request();
		HttpVar *getEnv(var name);
		HttpVar *getVar(var name, HttpVarType type);
		var post(var name);
		var get(var name);
		int envCount();
		var envDebug();
		var httpVarDebug();
		Method method();
	private:
		vector<HttpVar *> _vars;
		Method _method;
		bool _splitVars(var text,HttpVarType type);
		bool _createVar(var text,HttpVarType type);
	};
}