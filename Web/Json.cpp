#include "Web.h"
#include "Json.h"

namespace Web
{
	JNode::~JNode()
	{
		for(unsigned int i = 0; i < this->_children.size(); i++)
		{
			delete this->_children[i];
		}
		this->_children.clear();
	}
	JNode *JNode::append(JNode *node)
	{
		if(this != NULL)
		{
			if(this->_canAppend(node))
			{
				this->_children.push_back(node);
			}
		}
		return this;
	}
	JNode *JNode::appendTo(JNode *node)
	{
		if(node != NULL)
			if(node->append(this) == NULL)
				return NULL;
		return this;
	}
	JSON_TYPE JNode::getType()
	{
		return this->_type;
	}
	var JNode::print()
	{
		return this->printJson("{") + "}";
	}
	void JNode::_init()
	{
		this->_name = "";
		this->_type = JNULL;
	}
	JObject::JObject(var name)
	{
		this->_init();
		this->_name = name;
		this->_type = JOBJECT;
	}
	int JObject::_canAppend(JNode *node)
	{
		return true;
	}
	var JObject::printJson(var text)
	{
		text = text + "\"" + this->_name + "\": {";
		for(unsigned int i = 0; i < this->_children.size(); i++)
		{
			if( i != 0)
				text = text + ",";
			text = this->_children[i]->printJson(text);
		}

		text = text + "}";
		return text;
	}
	JAttr::JAttr(var name, var value)
	{
		value.replace("\"","\\\"");
		value.replace("\n","\\n");
		this->_init();
		this->_name = name;
		this->_val = value;
		this->_type = JATTR;
	}
	int JAttr::_canAppend(JNode *node)
	{
		return false;
	}
	var JAttr::printJson(var text)
	{
		text = text + "\"" + this->_name + "\": \"" + this->_val + "\"";
		return text;
	}
	var JAttr::value()
	{
		if(this == NULL)
			return NULL;
		return this->_val;
	}
	JNode *JAttr::value(var val)
	{
		if(this == NULL)
			return NULL;
		this->_val = val;
		return this;
	}
	JArray::JArray(var name)
	{
		this->_init();
		this->_name = name;
		this->_type = JARRAY;
	}
	int JArray::_canAppend(JNode *node)
	{
		return node->getType() == JARRAY_ITEM;
	}
	var JArray::printJson(var text)
	{
		text = text + "\"" + this->_name + "\": [";

		for(unsigned int i = 0; i < this->_children.size(); i++)
		{
			if( i != 0)
				text = text + ",";
			text = this->_children[i]->printJson(text);
		}
		text = text + "]";
		return text;
	}
	JArrayItem::JArrayItem()
	{
		this->_init();
		this->_type = JARRAY_ITEM;
	}
	int JArrayItem::_canAppend(JNode *node)
	{
		return true;
	}
	var JArrayItem::printJson(var text)
	{
		text = text + "{";

		for(unsigned int i = 0; i < this->_children.size(); i++)
		{
			if( i != 0)
				text = text + ",";
			text = this->_children[i]->printJson(text);
		}
		text = text + "}";
		return text;
	}
	Json::Json()
	{
		this->_root = new JObject("root");
		this->_status = (new JAttr("status",1));
		this->_status->appendTo(this->_root);
		this->_message = (new JAttr("message",""));
		this->_message->appendTo(this->_root);
		this->_data = NULL;
	}
	Json::~Json()
	{
		delete this->_root;
	}
	JNode *Json::append(JNode *node)
	{
		if(this->_data == NULL)
		{
			this->_data = new JObject("data");
			this->_data->appendTo(this->_root);
		}
		this->_data->append(node);
		return this->_data;
	}
	void Json::setStatus(bool success, var status)
	{
		this->_status->value(success);
		this->_message->value(status);
	}
	var Json::render()
	{
		return this->_root->print();
	}
}