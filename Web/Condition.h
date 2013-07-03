#pragma once

#include "Web.h"

using namespace std;

namespace Web
{

	enum CONDITION_OP { OP_UNDEFINED, OP_EQ, OP_IN, OP_INEQ, OP_LT, OP_GT, OP_LET, OP_GET, OP_LIKE, OP_BETWEEN };
	enum LOGICAL_OP { LOP_NULL, LOP_AND, LOP_OR };


	class ConditionList
	{
		friend class Condition;
		template <class T = ConditionList>
		friend class ConditionQuery;
		friend class Query;
	protected:
		ConditionList();
		~ConditionList();
		Condition *where(var field);
		ConditionList *where(ConditionList *cond);
		Condition *and(var field);
		ConditionList *and(ConditionList *cond);
		Condition *or(var field);
		ConditionList *or(ConditionList *cond);
		var _printConditions();
	private:
		Condition *_add(Condition * item);
		List<Condition *> _conditions;
	};

	template <class T>
	class ConditionListT : public ConditionList
	{
	public:
		ConditionQuery<T> *where(var field)
		{
			return (ConditionQuery<T>*)ConditionList::where(field);
		}
		T *where(ConditionList *cond)
		{
			return (T *)ConditionList::where(cond);
		}
		ConditionQuery<T> *and(var field)
		{
			return (ConditionQuery<T>*)ConditionList::and(field);
		}
		T *and(ConditionList *cond)
		{
			return (T *)ConditionList::and(cond);
		}
		ConditionQuery<T> *or(var field)
		{
			return (ConditionQuery<T>*)ConditionList::or(field);
		}
		T *or(ConditionList *cond)
		{
			return (T *)ConditionList::or(cond);
		}
	};

	
	
	class Condition
	{
		friend class ConditionList;
	public:
		Condition(var field);
		~Condition();
		ConditionList *equal(var value);
		ConditionList *in(Select *s);
		ConditionList *notEqual(var value);
		ConditionList *like(var value);
		ConditionList *greaterThan(var value);
		ConditionList *lessThan(var value);
		ConditionList *greaterEqThan(var value);
		ConditionList *lessEqThan(var value);
		ConditionList *between(var value1, var value2);
	protected:
		var _print();
	private:
		void _initCond(CONDITION_OP op, var value1, var value2 = "");
		Condition(ConditionList *parent, var field, LOGICAL_OP lop);
		var _field;
		var _value1, _value2;
		CONDITION_OP _op;
		LOGICAL_OP _lop;
		ConditionList *_parent;
		ConditionList *_block;
		bool _isBlock;
	};
	
	template <class T = ConditionList>
	class ConditionQuery : public Condition
	{
		friend class ConditionList;
	public:
		ConditionQuery(var field)
			:Condition(field) {}
		ConditionQuery(ConditionList *parent, var field, LOGICAL_OP lop)
			:Condition(parent, field, lop) {}
		T *equal(var value)
		{
			return (T*)Condition::equal(value);
		}
		T *in(Select *s)
		{
			return (T*)Condition::in(s);
		}
		T *notEqual(var value)
		{
			return (T*)Condition::notEqual(value);
		}
		T *like(var value)
		{
			return (T*)Condition::like(value);
		}
		T *greaterThan(var value)
		{
			return (T*)Condition::greaterThan(value);
		}
		T *lessThan(var value)
		{
			return (T*)Condition::lessThan(value);
		}
		T *greaterEqThan(var value)
		{
			return (T*)Condition::greaterEqThan(value);
		}
		T *lessEqThan(var value)
		{
			return (T*)Condition::lessEqThan(value);
		}
		T *between(var value1, var value2)
		{
			return (T*)Condition::between(value1, value2);
		}

	private:
		
	};
	

}