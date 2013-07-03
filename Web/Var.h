#pragma once

#include "Web.h"
#include <malloc.h>
#include <math.h>
#include <regex>

using namespace std;

namespace Web
{
	enum VAR_TYPES { 
		TYPE_UNDEFINED,		// 
		TYPE_DATA,			// 01/01/2012
		TYPE_CHAR,			// 'c'
		TYPE_INT,			// 3, 5
		TYPE_DOUBLE,		// 3.5
		TYPE_STRING			// "ciao"

	};
	
	enum VAR_OPERATOR{ VAR_ADD, VAR_REM, VAR_MUL, VAR_DIV };
	class var
	{
		friend bool operator == (const var& first,const var& second)
		{
			return (((var *)&first)->toS() == ((var *)&second)->toS());
		}
		friend bool operator != (const var& first,const var& second)
		{
			return !(first == second);
		}
		friend var operator + (const var& first,const var& second)
		{
			var ris;
			ris = ((var *)&second)->_operation(((var *)&first), VAR_ADD);
			return ris;
		}
		friend var operator - (const var& first,const var& second)
		{
			var ris;
			ris = ((var *)&second)->_operation(((var *)&first), VAR_REM);
			return ris;
		}
		friend var operator * (const var& first,const var& second)
		{
			var ris;
			ris = ((var *)&second)->_operation(((var *)&first), VAR_MUL);
			return ris;
		}
		friend var operator / (const var& first,const var& second)
		{
			var ris;
			ris = ((var *)&second)->_operation(((var *)&first), VAR_DIV);
			return ris;
		}
		friend var& operator += (var& first,const var& second)
		{
			first = first + second;
			return first;
		}
		friend var& operator -= (var& first,const var& second)
		{
			first = first - second;
			return first;
		}
		friend var& operator *= (var& first,const var& second)
		{
			first = first * second;
			return first;
		}
		friend var& operator /= (var& first,const var& second)
		{
			first = first / second;
			return first;
		}
		friend var& operator << (var& first,const var& second)
		{
			first = first + second;
			return first;
		}
		friend ostream& operator<<(ostream& os, const var& value)
		{
			os << ((var *)&value)->toS();
			return os;
		}
	public:
		var()
		{
			this->_value = NULL;
			this->_type = TYPE_UNDEFINED;
		}
		var(const var& value)
		{
			this->_type = value._type;
			if(value._type == TYPE_STRING)
				this->_value = new string(*(string *)value._value);
			else
			{
				this->_value = (void *)malloc(sizeof(value._value)+1);
				memcpy(this->_value, value._value, sizeof(value._value));
			}
		}
		~var()
		{
			delete this->_value;
		}
		var(string value)
		{
			this->_value = new string(value);
			this->_type = TYPE_STRING;
		}
		var(const char value[])
		{
			this->_value = new string(value);
			this->_type = TYPE_STRING;
		}
		var(char value)
		{
			this->_value = new char(value);
			this->_type = TYPE_CHAR;
		}
		var(int value)
		{
			this->_value = new int(value);
			this->_type = TYPE_INT;
		}
		var(double value)
		{
			this->_value = new double(value);
			this->_type = TYPE_DOUBLE;
		}
		var& operator = (string value)
		{
			delete this->_value;
			this->_value = new string(value);
			this->_type = TYPE_STRING;
			return *this;
		}
		var& operator = (const char value[])
		{
			delete this->_value;
			this->_value = new string(value);
			this->_type = TYPE_STRING;
			return *this;
		}
		var& operator = (const var& value)
		{
			delete this->_value;
			this->_type = value._type;
			if(value._type == TYPE_STRING)
				this->_value = new string(*(string *)value._value);
			else
			{	
				this->_value = (void *)malloc(sizeof(value._value)+1);
				memcpy(this->_value, value._value, sizeof(value._value)+1);
			}
			return *this;
		}
		var& operator = (const char& value)
		{
			delete this->_value;
			this->_value = new char(value);
			this->_type = TYPE_CHAR;
			return *this;
		}
		var& operator = (const int& value)
		{
			delete this->_value;
			this->_value = new int(value);
			this->_type = TYPE_INT;
			return *this;
		}	
		var& operator = (const double& value)
		{
			delete this->_value;
			this->_value = new double(value);
			this->_type = TYPE_DOUBLE;
			return *this;
		}
		int find(var p, int from = 0)
		{
			return this->toS().find(p.toS(), from);
		}
		var substr(int from)
		{
			return this->toS().substr(from);
		}
		var substr(int from, int len)
		{
			return this->toS().substr(from, len);
		}
		string toS();
		const char* toC();
		var toSql()
		{
			var ris = "";
			switch(this->_type)
			{
			case TYPE_DATA:
				ris<<"{d '"<<*this<<"' }";
				break;
			case TYPE_CHAR:
				ris<<"'"<<*this<<"'";
				break;
			case TYPE_INT:
				ris<<*this;
				break;
			case TYPE_DOUBLE:
				ris<<*this;
				break;
			case TYPE_STRING:
				ris<<"'"<<*this<<"'";
				break;
			}
			return ris;
		}
	private:
		VAR_TYPES _type;
		void *_value;
		var _operation(var *var1, VAR_OPERATOR op)
		{
			var res;
			var *var2 = this;
			if( (var1->_type == TYPE_INT || var1->_type == TYPE_DOUBLE) && (var2->_type == TYPE_INT || var2->_type == TYPE_DOUBLE) )
			{
				if(var1->_type == TYPE_DOUBLE || var2->_type == TYPE_DOUBLE)
				{
					res._type = TYPE_DOUBLE;
					res._value = new double((var1->_type == TYPE_DOUBLE ? *(double *)var1->_value : *(int *)var1->_value));
					switch(op)
					{
					case VAR_ADD:
						*(double *)res._value += (var2->_type == TYPE_DOUBLE ? *(double *)var2->_value : *(int *)var2->_value);
						break;
					case VAR_REM:
						res._value = new double( 
							(var1->_type == TYPE_DOUBLE ? *(double *)var1->_value : *(int *)var1->_value) 
							- 
							(var2->_type == TYPE_DOUBLE ? *(double *)var2->_value : *(int *)var2->_value) );
						break;
					case VAR_MUL:
						res._value = new double( 
							(var1->_type == TYPE_DOUBLE ? *(double *)var1->_value : *(int *)var1->_value) 
							* 
							(var2->_type == TYPE_DOUBLE ? *(double *)var2->_value : *(int *)var2->_value) );
						break;
					case VAR_DIV:
						res._value = new double( 
							(var1->_type == TYPE_DOUBLE ? *(double *)var1->_value : *(int *)var1->_value) 
							/ 
							(var2->_type == TYPE_DOUBLE ? *(double *)var2->_value : *(int *)var2->_value) );
						break;
					}
				}
				else
				{
					switch(op)
					{
					case VAR_ADD:
						res._type = TYPE_INT;
						res._value = new int( *(int *)var1->_value + *(int *)var2->_value );
						break;
					case VAR_REM:
						res._type = TYPE_INT;
						res._value = new int( *(int *)var1->_value - *(int *)var2->_value );
						break;
					case VAR_MUL:
						res._type = TYPE_INT;
						res._value = new int( *(int *)var1->_value * *(int *)var2->_value );
						break;
					case VAR_DIV:
						res._type = TYPE_DOUBLE;
						res._value = new double( *(int *)var1->_value / *(int *)var2->_value );
						break;
					}
					
				}
			}
			else
			{
				res = var1->toS() + var2->toS();
			}
			return res;
		}
	};

}