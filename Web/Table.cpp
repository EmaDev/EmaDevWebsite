#include "Web.h"
#include "Table.h"

namespace Web
{
	
	Table::Table(var tableName, string alias = "")
	{
		this->_name = tableName;
		this->_alias = alias;
		this->_type = TABLE_TABLE;
		this->_select = NULL;
	}
	Table::Table(Select *select, string alias = "")
	{
		this->_select = select;
		this->_alias = alias;
		this->_type = TABLE_SELECT;
	}
	var Table::_print()
	{
		var table = " ";
		if(this->_type == TABLE_TABLE)
		{
			table += this->_name;
		}
		else
		{
			table += "( ";
			table += this->_select->getSql();
			table += ")";
		}
		if(!(this->_alias == ""))
		{
			table += " " + this->_alias;
		}
		return table;
	}


}