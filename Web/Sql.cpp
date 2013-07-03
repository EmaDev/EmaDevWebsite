#include "Web.h"
#include "Sql.h"

namespace Web
{

	SqlException::SqlException(unsigned handletype, const SQLHANDLE& handle)
	{
		SQLCHAR sqlstate[1024];
		SQLCHAR message[1024];
		if(SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
		{
			this->_msg = (char *)message;
			this->_state = (char *)sqlstate;
		}
	}
	SqlException::~SqlException()
	{
	
	}
	string SqlException::message()
	{
		return this->_msg;
	}
	string SqlException::state()
	{
		return this->_state;
	}


	Sql::Sql(var DSN)
	{
		this->_connected = false;
		this->_dsn = DSN;


		if(	SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->_handle)
			|| SQL_SUCCESS!=SQLSetEnvAttr(this->_handle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, 0) 
			|| SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_DBC, this->_handle, &this->_connection))
		{
			this->disconnect();
			return;
		}
		SQLCHAR retconstring[1024];

		this->_connected = true;

		switch(SQLDriverConnect (this->_connection,
					NULL,
					(SQLCHAR*)string("DSN=").append(DSN.toS()).append(";").c_str(),
					SQL_NTS,
					retconstring,
					1024,
					NULL,
					SQL_DRIVER_NOPROMPT))
		{
			case SQL_SUCCESS_WITH_INFO:
				break;
			case SQL_SUCCESS:
				break;
			default:
				this->_throwError(SQL_HANDLE_DBC, this->_connection);
				break;
		}
		
	}
	void Sql::_exec(string sql)
	{
		if(!this->_manageErrors(SQLAllocHandle(SQL_HANDLE_STMT, this->_connection, &this->_state)))
		{
			this->_throwError(SQL_HANDLE_STMT, this->_state);
		}
		if( !this->_manageErrors(SQLExecDirect(this->_state, (SQLCHAR*)sql.c_str(), SQL_NTS)))
		{
			this->_throwError(SQL_HANDLE_STMT, this->_state);
		}

		SQLNumResultCols(this->_state, &this->_columnsCount);

 		/*if( !this->_manageErrors(SQLGetDescField(hdesc,NULL,SQL_DESC_COUNT,&this->_columnsCount,NULL,NULL)))
		{
			this->_throwError(SQL_HANDLE_STMT, this->_state);
		}*/


	}
	bool Sql::_fetch()
	{
		this->_fields.clear();
		if(SQLFetch(this->_state)==SQL_SUCCESS)
		{
			char fieldName[128 + 1] = "";
			var fieldValue;
			SQLSMALLINT fieldType = 0;

			SQLGetStmtAttr(this->_state,SQL_ATTR_IMP_ROW_DESC,&this->_desc,NULL,NULL);

			for(unsigned i = 1; i <= this->_columnsCount; i++)
			{
				if(!this->_manageErrors(SQLGetDescField(this->_desc, i,SQL_DESC_NAME , fieldName, sizeof(fieldName), NULL)))
				{
					this->_throwError(SQL_HANDLE_STMT, this->_state);
				}
				if(!this->_manageErrors(SQLGetDescField(this->_desc, i,SQL_DESC_TYPE , &fieldType, 0, NULL)))
				{
					this->_throwError(SQL_HANDLE_STMT, this->_state);
				}
				fieldValue = this->_extactValue(fieldType, i);
				this->_fields.add(fieldName, fieldValue);
			}
			return true;
		}
		else
			return false;
	}
	var Sql::_get(var field)
	{
		return this->_fields.find(field);
		/*SQLGetStmtAttr(this->_state,SQL_ATTR_IMP_ROW_DESC,&this->_desc,NULL,NULL);

		char fieldName[128 + 1] = "";
		var ris;
		SQLSMALLINT fieldType = 0;

		for(unsigned i = 1; i <= this->_columnsCount; i++)
		{
			if(!this->_manageErrors(SQLGetDescField(this->_desc, i,SQL_DESC_NAME , fieldName, sizeof(fieldName), NULL)))
			{
				this->_throwError(SQL_HANDLE_STMT, this->_state);
			}
			if(fieldName == field)
			{
				if(!this->_manageErrors(SQLGetDescField(this->_desc, i,SQL_DESC_TYPE , &fieldType, 0, NULL)))
				{
					this->_throwError(SQL_HANDLE_STMT, this->_state);
				}

				return this->_extactValue(fieldType, i);
			}
		}
		return NULL;*/
	}
	var Sql::_extactValue(SQLSMALLINT fieldType, int index)
	{
		var ris;
		void *bufferValue;
		int valueLen = 0;
		if(!this->_manageErrors(SQLGetDescField(this->_desc, index,SQL_DESC_LENGTH , &valueLen, 0, NULL)))
		{
			this->_throwError(SQL_HANDLE_STMT, this->_state);
		}
		switch(fieldType)
		{
		case SQL_CHAR:
			bufferValue = new char();
			break;
		case SQL_VARCHAR:
			bufferValue = new char[valueLen + 1];
			if(this->_extactValue(SQL_C_CHAR, index, bufferValue, valueLen + 1))
			{
				ris = (char *)bufferValue;
			}
			break;
		case SQL_LONGVARCHAR:
			ris = "Nedd to test type : Longvarchar";
			break;
		case SQL_WCHAR:
			ris = "Nedd to test type : Wchar";
			break;
		case SQL_WVARCHAR:
			ris = "Nedd to test type : Wvarchar";
			break;
		case SQL_WLONGVARCHAR:
			ris = "Nedd to test type : Wlongvarchar";
			break;
		case SQL_DECIMAL:
			ris = "Nedd to test type : Decimal";
			break;
		case SQL_NUMERIC:
			bufferValue = new int();
			break;
		case SQL_SMALLINT:
			ris = "Nedd to test type : Smallint";
			break;
		case SQL_INTEGER:
			bufferValue = new int();
			if(this->_extactValue(fieldType, index, bufferValue, sizeof(int)))
			{
				ris = *(int *)bufferValue;
			}
			break;
		case SQL_REAL:
			ris = "Nedd to test type : Real";
			break;
		case SQL_FLOAT:
			ris = "Nedd to test type : Float";
			break;
		case SQL_DOUBLE:
			ris = "Nedd to test type : Double";
			break;
		case SQL_BIT:
			ris = "Nedd to test type : Bit";
			break;
		case SQL_TINYINT:
			ris = "Nedd to test type : Tinyint";
			break;
		case SQL_BIGINT:
			ris = "Nedd to test type : Bigint";
			break;
		case SQL_BINARY:
			ris = "Nedd to test type : Binary";
			break;
		case SQL_VARBINARY:
			ris = "Nedd to test type : Varbinary";
			break;
		case SQL_LONGVARBINARY:
			ris = "Nedd to test type : Longvarbinary";
			break;
		case SQL_TYPE_DATE:
			ris = "Nedd to test type : Type_date";
			break;
		case SQL_TYPE_TIME:
			ris = "Nedd to test type : Type_time";
			break;
		case SQL_TYPE_TIMESTAMP:
			ris = "Nedd to test type : Type_timestamp";
			break;
		case SQL_INTERVAL_MONTH:
			ris = "Nedd to test type : Interval_month";
			break;
		case SQL_INTERVAL_YEAR:
			ris = "Nedd to test type : Interval_year";
			break;
		case SQL_INTERVAL_YEAR_TO_MONTH:
			ris = "Nedd to test type : Interval_year_to_month";
			break;
		case SQL_INTERVAL_DAY:
			ris = "Nedd to test type : Interval_day";
			break;
		case SQL_INTERVAL_HOUR:
			ris = "Nedd to test type : Interval_hour";
			break;
		case SQL_INTERVAL_MINUTE:
			ris = "Nedd to test type : Interval_minute";
			break;
		case SQL_INTERVAL_SECOND:
			ris = "Nedd to test type : Interval_second";
			break;
		case SQL_INTERVAL_DAY_TO_HOUR:
			ris = "Nedd to test type : Interval_day_to_hour";
			break;
		case SQL_INTERVAL_DAY_TO_MINUTE:
			ris = "Nedd to test type : Interval_day_to_minute";
			break;
		case SQL_INTERVAL_DAY_TO_SECOND:
			ris = "Nedd to test type : Interval_day_to_second";
			break;
		case SQL_INTERVAL_HOUR_TO_MINUTE:
			ris = "Nedd to test type : Interval_hour_to_minute";
			break;
		case SQL_INTERVAL_HOUR_TO_SECOND:
			ris = "Nedd to test type : Interval_hour_to_second";
			break;
		case SQL_INTERVAL_MINUTE_TO_SECOND:
			ris = "Nedd to test type : Interval_minute_to_second";
			break;
		}
		delete bufferValue;
		return ris;
	}
	bool Sql::_extactValue(SQLSMALLINT fieldType,int index, void *ris, SQLSMALLINT size)
	{
		SQLINTEGER indicator;
		if(!this->_manageErrors(SQLGetData(this->_state, index, fieldType, ris, size, &indicator)))
		{
			this->_throwError(SQL_HANDLE_STMT, this->_state);
		}
		if(indicator == SQL_NULL_DATA)
		{
			return false;
		}
		return true;
	}
	bool Sql::_manageErrors(SQLRETURN status)
	{
		switch(status)
		{
		case SQL_SUCCESS:
			return true;
			break;
		case SQL_SUCCESS_WITH_INFO:
			return true;
			break;
		case SQL_ERROR:
			return false;
			break;
		case SQL_NO_DATA:
			return false;
			break;
		case SQL_INVALID_HANDLE:
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	void Sql::_throwError(unsigned handletype, const SQLHANDLE& handle)
	{
		throw SqlException(handletype, handle);
		this->disconnect();
	}
	void Sql::disconnect()
	{
		if(this != NULL)
		{
			SQLDisconnect(this->_connection);
			SQLFreeHandle(SQL_HANDLE_DBC, this->_connection);
			SQLFreeHandle(SQL_HANDLE_ENV, &this->_handle);
			this->_connected = false;
		}
	}
	Sql::~Sql()
	{
		this->disconnect();
	}
	Select* Sql::select()
	{
		return new Select(this);
	}

 }