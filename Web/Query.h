#pragma once

#include "Web.h"
#include "Sql.h"
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
	class QueryTable
	{
	protected:
		
	};

	class Query
	{
	public:
		Query(Sql *sql);
		~Query();
		void exec();
		virtual var getSql() = 0;
	protected:
		Sql *_sql;
	private:
	};

	class Select : public Query, public ConditionListT<Select>, public TableList<Select>, public ValueList<Select>, public Order<Select>
	{
	public:
		Select(Sql *sql);
		var getSql();
		bool fetch();
		var get(var value);
	private:
	};

	class Delete : public Query, public ConditionListT<Delete>, public TableList<Delete>
	{
	public:
		Delete(Sql *sql);
		var getSql();
	private:
	};

	class Insert : public Query, public TableList<Insert>
	{
	public:
		Insert(Sql *sql);
		var getSql();
	private:
	};

}