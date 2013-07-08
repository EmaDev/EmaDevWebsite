#pragma once

#include "Web.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <odbcinst.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

namespace Web
{

	class SqlException:public exception
	{
	public:
		SqlException(unsigned handletype, const SQLHANDLE& handle);
		~SqlException();
		string message();
		string state();
	private:
		string _msg;
		string _state;
	};
	 



	class SqlField
	{
	public:
		var name;
		SQLSMALLINT type;
		long size;
		void *buffer;
	};



	class Sql
	{
		friend class Query;
		friend class Select;
	public:
		Sql(var DSN, void (*excepionFunction)(SqlException ex));
		Sql(var DSN);
		~Sql();
		bool connected();
		void disconnect();
		Select* select();
	protected:
		void _exec(string sql);
		bool _fetch();
		var _get(var value);
	private:
		List<SqlField *> _fields;
		var _extactValue(SQLSMALLINT fieldType, int index);
		bool _extactValue(SQLSMALLINT fieldType,int index, void *ris, SQLSMALLINT size);
		SQLSMALLINT _columnsCount;
		void _throwError(unsigned handletype, const SQLHANDLE& handle);
		bool _connected;
		var _dsn;
		bool _manageErrors(SQLRETURN status);
		SQLHANDLE _state;
		SQLHANDLE _connection;
		SQLHANDLE _handle;
		SQLHDESC _desc; 
	};
}