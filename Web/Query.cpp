#include "Web.h"
#include "Query.h"

namespace Web
{
	
	Query::Query(Sql *sql)
	{
		this->_sql = sql;

	}
	Select::Select(Sql *sql)
		:Query(sql) {}
	Delete::Delete(Sql *sql)
		:Query(sql) {}
	Insert::Insert(Sql *sql)
		:Query(sql) {}


	Query::~Query()
	{
	
	}
	void Query::exec()
	{
		this->_sql->_exec(this->getSql().toS());
	}


	var Select::getSql()
	{
		var sql = "SELECT";
		List<var> values = this->_getValues();
		if(values.size() != 0)
		{
			for(unsigned i = 0; i < values.size(); i++)
			{
				if(i!=0)
					sql += ",";
				sql += " " + values.at(i);
			}
		}
		else
		{
			sql += " *";
		}
		sql += " FROM" + this->_printTables();
		var conditions = this->_printConditions();
		if(conditions != "")
			sql += " WHERE" + conditions;
		List<var> order = this->_getOrder();
		if(order.size() != 0)
		{
			sql += " ORDER BY";
			for(unsigned i = 0; i < order.size(); i++)
			{
				if(i!=0)
					sql += ",";
				sql += " " + order.at(i);
			}
		}
		return sql;
	}
	bool Select::fetch()
	{
		return this->_sql->_fetch();
	}
	var Select::get(var value)
	{
		return this->_sql->_get(value);
	}

	var Delete::getSql()
	{
		var sql = "Delete";
		sql += " FROM" + this->_printTables();
		var conditions = this->_printConditions();
		if(conditions != "")
			sql += " WHERE" + conditions;
		return sql;
	}


	var Insert::getSql()
	{
		var sql = "INSERT INTO ";
		sql += this->_printTables();
		return sql;
	}
}