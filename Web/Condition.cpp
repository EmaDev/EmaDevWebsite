#include "Web.h"
#include "Condition.h"

namespace Web
{
	

	ConditionList::ConditionList()
	{
	
	}
	ConditionList::~ConditionList()
	{
		for(unsigned i = this->_conditions.size() -1; i >= 0; i--)
		{
			delete this->_conditions.at(i);
		}
		this->_conditions.clear();
	}
	Condition *ConditionList::where(var field)
	{
		return this->_add(new Condition(this, field, LOP_NULL));
	}
	ConditionList *ConditionList::where(ConditionList *cond)
	{
		Condition *tmp = cond->_conditions.first();
		tmp->_lop = LOP_NULL;
		this->_conditions.append(tmp);
		return this;
	}
	Condition *ConditionList::and(var field)
	{
		return this->_add(new Condition(this, field, LOP_AND));
	}
	ConditionList *ConditionList::and(ConditionList *cond)
	{
		Condition *tmp = cond->_conditions.first();
		tmp->_lop = LOP_AND;
		this->_conditions.append(tmp);
		return this;
	}
	Condition *ConditionList::or(var field)
	{
		return this->_add(new Condition(this, field, LOP_OR));
	}
	ConditionList *ConditionList::or(ConditionList *cond)
	{
		Condition *tmp = cond->_conditions.first();
		tmp->_lop = LOP_OR;
		this->_conditions.append(tmp);
		return this;
	}
	Condition *ConditionList::_add(Condition * item)
	{
		Condition *tmp = item->_parent->_conditions.first();
		if(tmp!= NULL && tmp->_isBlock)
			tmp->_block->_conditions.append(item);
		else
			this->_conditions.append(item);
		return item;
	}
	var ConditionList::_printConditions()
	{
		var result = " ";
		if(this->_conditions.size() > 0)
		{
			for(unsigned i = 0; i < this->_conditions.size(); i++)
			{
				result += this->_conditions.at(i)->_print();
			}
			return result;
		}
		else
			return "";
	}


	Condition::Condition(var field)	
	{
		this->_isBlock = true;
		this->_parent = new ConditionList();
		this->_parent->_add(this);
		this->_block = new ConditionList();
		

		this->_block->_add(
			new Condition(this->_block, field, LOP_NULL)
		);

		this->_op = OP_UNDEFINED;
		this->_lop = LOP_NULL;
	}
	Condition::~Condition()
	{
	
	}
	ConditionList *Condition::equal(var value)
	{
		_initCond(OP_EQ, value);
		return this->_parent;
	}
	ConditionList *Condition::notEqual(var value)
	{
		_initCond(OP_INEQ, value);
		return this->_parent;
	}
	ConditionList *Condition::like(var value)
	{
		_initCond(OP_LIKE, value);
		return this->_parent;
	}
	ConditionList *Condition::greaterThan(var value)
	{
		_initCond(OP_GT, value);
		return this->_parent;
	}
	ConditionList *Condition::lessThan(var value)
	{
		_initCond(OP_LT, value);
		return this->_parent;
	}
	ConditionList *Condition::greaterEqThan(var value)
	{
		_initCond(OP_GET, value);
		return this->_parent;
	}
	ConditionList *Condition::lessEqThan(var value)
	{
		_initCond(OP_LET, value);
		return this->_parent;
	}
	ConditionList *Condition::between(var value1, var value2)
	{
		_initCond(OP_BETWEEN, value1, value2);
		return this->_parent;
	}
	void Condition::_initCond(CONDITION_OP op, var value1, var value2)
		{
			Condition *tmp = this;	
			if(this->_isBlock)
				tmp = this->_block->_conditions.at(0);
			tmp->_value1 = value1;
			this->_value2 = value2;
			tmp->_op = op;
		}
	var Condition::_print()
	{
		var result = " ";
		if(this->_lop == LOP_AND)
			result += "AND ";
		else if(this->_lop == LOP_OR)
			result += "OR ";

		if(this->_isBlock)
			return result + " (" + this->_block->_printConditions() + " )";

		result += this->_field;

		switch(this->_op)
		{
		case OP_UNDEFINED:
			return "";
			break;
		case OP_EQ:
			result += " = " + this->_value1.toSql();
			break;
		case OP_INEQ:
			result +=" != " + this->_value1.toSql();
			break;
		case OP_LT:
			result +=" < " + this->_value1.toSql();
			break;
		case OP_GT:
			result +=" > " + this->_value1.toSql();
			break;
		case OP_LET:
			result +=" <= " + this->_value1.toSql();
			break;
		case OP_GET:
			result +=" >= " + this->_value1.toSql();
			break;
		case OP_LIKE:
			result +=" LIKE " + this->_value1.toSql();
			break;
		case OP_BETWEEN:
			result +=" BETWEEN " + this->_value1.toSql() + " AND " + this->_value2.toSql();
			break;
		}
		return result;
	}
	Condition::Condition(ConditionList *parent, var field, LOGICAL_OP lop)
	{
		this->_isBlock = false;
		this->_parent = parent;
		this->_field = field;
		this->_op = OP_UNDEFINED;
		this->_lop = lop;
	}
}