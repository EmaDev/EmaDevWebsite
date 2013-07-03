#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	class Query;
	class Select;

	enum TABLE_TYPE { TABLE_TABLE, TABLE_SELECT };

	class Table
	{
		template <class T>
		friend class TableList;
	public:
		Table(var tableName, string alias);
		Table(Select *select, string alias);
	private:
		var _print();
		var _name;
		var _alias;
		Select *_select;
		TABLE_TYPE _type;
	};

	template <class T>
	class TableList
	{

	public:
		TableList() {}
		T *from(var tableName, string alias = "")
		{
			this->_tables.append(new Table(tableName, alias));
			return (T *)this;
		}
		T *from(Select *select, string alias = "")
		{
			this->_tables.append(new Table(select, alias));
			return (T *)this;
		}
		~TableList()
		{
			for(unsigned i = this->_tables.size() -1; i >= 0; i--)
				delete this->_tables.at(i);
			this->_tables.clear();
		}
	protected:
		var _printTables()
		{
			var tables = "";
			for(unsigned i = 0; i < this->_tables.size(); i++)
			{
				if(i != 0)
					tables += ",";
				tables += this->_tables.at(i)->_print();
			}
			return tables;
		}
	private:
		List<Table *> _tables;
	};

}
