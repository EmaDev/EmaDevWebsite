#pragma once

#include "Web.h"
#include <vector>
using namespace std;

namespace Web{

	template <class T> 
	class List
	{
	public:
		List();
		List<T>* append(T item);
		T at(unsigned index);
		T last();
		T first();
		unsigned size();
		void clear();
		~List();
	private:
		vector<T> _list;
	};


	template <class T>
	List<T>::List()
	{
	}

	template <class T>
	List<T>::~List()
	{
	}
	
	template <class T>
	List<T>* List<T>::append(T item)
	{
		this->_list.push_back(item);
		return this;
	}

	template <class T>
	T List<T>::at(unsigned index)
	{
		if(index >= 0 && index < this->size())
			return this->_list[index];
		else
			return NULL;
	}

	template <class T>
	T List<T>::first(){
		return this->at(0);
	}

	template <class T>
	T List<T>::last(){
		return this->at(this->size()-1);
	}

	template <class T>
	unsigned List<T>::size()
	{
		unsigned size = this->_list.size();
		return size;
	}
	template <class T>
	void List<T>::clear()
	{
		this->_list.clear();
	}

	class KeyValue
	{
	public:
		KeyValue(int null);
		KeyValue(var key, var value);
		KeyValue(const KeyValue& kv);
		var key();
		var value();
	private:
		var _key;
		var _value;
	};

	class Dictionary : public List<KeyValue>
	{
	public:
		bool add(var key, var value);
		bool add(KeyValue& kv);
		var find(var key);
		bool exist(var key);
		var& operator [] (const var& key);
	private:
	};
}