#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	enum JSON_TYPE { JNULL, JOBJECT, JATTR, JARRAY, JARRAY_ITEM };
	class JNode
	{
	public:
		~JNode();
        JNode *append(JNode *node);
		JNode *appendTo(JNode *node);
        JSON_TYPE getType();
        var print();
        virtual var printJson(var text) = 0;
    protected:
    	void _init();
        JSON_TYPE _type;
        var _name;
        vector<JNode *> _children;
        virtual int _canAppend(JNode *node) = 0;
	};
	class JObject : public JNode
	{
	public:
    	JObject(var name);
		var printJson(var text);
	private:
    	int _canAppend(JNode *node);
	};
	class JAttr : public JNode
	{
	public:
		JAttr(var name, var value);
		var value();
		JNode *value(var val);
		var printJson(var tjson);
	private:
		int _canAppend(JNode *node);
		var _val;
	};
	class JArray : public JNode
	{
	public:
    	 JArray(var name);
    	 var printJson(var text);
	private:
    	 int _canAppend(JNode *node);
	};
	class JArrayItem : public JNode
	{
	public:
    	JArrayItem();
    	var printJson(var text);
	private:
    	int _canAppend(JNode *node);
	};

	class Json
	{
	public:
		Json();
		~Json();
		JNode *append(JNode *node);
		void setStatus(bool status, var message);
		var render();
	private:
		JObject *_root;
		JAttr *_status;
		JAttr *_message;
		JObject *_data;
	};
}