#include "Web.h"
#include "Tag.h"

namespace Web
{

	static char* labelTag[] = {
		"", // TAG_DELIMITER_BLOCK
		"html",
		"head",
		"body",
		"div",
		"p",
		"title",
		"link",
		"script",
		"span",
		"", // TAG_DELIMITER_INLINE
		"img",
		"canvas",
		"", // TAG_DELIMITER_SPECIAL
		"",
		""
	};
	static const char *TagDelimiter[3][4]  = 
	{
		{ "<", ">", "</", ">" },
		{ "<", ">", "", "" },
		{ "", "", "", "" }
	};
	Tag::Tag(TAG_NAME name)
	{
		if(name == TAG_DELIMITER_BLOCK || name == TAG_DELIMITER_INLINE || name == TAG_DELIMITER_SPECIAL)
			throw new exception("Unsupported Tag name.");
		if(name > TAG_DELIMITER_BLOCK)
		{
			if(name < TAG_DELIMITER_INLINE)
			{
				this->_type = TAG_TYPE_BLOCK;
				this->_container = true;
			}
			else
			{
				if(name < TAG_DELIMITER_SPECIAL)
				{
					this->_type = TAG_TYPE_INLINE;
					this->_container = false;
				}
				else
				{
					this->_type = TAG_TYPE_SPECIAL;
					if(name == COMMENT)
						this->_container = true;
					else
						this->_container = false;
				}
			}
		}
		this->_parent = NULL;
		this->_name = name;
	}
	 
	Tag* Tag::append(Tag *item)
	{
		if(this == NULL)
			return NULL;

		if(item != NULL && this->_container)
		{
			if(item->_parent == NULL)
			{
				item->_parent = this;
				this->_children.append(item);
			}
		}
		return this;
	}
	
	Tag* Tag::append(var text)
	{
		if(this == NULL)
			return NULL;
		if(this->_container)
		{
			Tag *tmp = new Tag(TEXT);
			tmp->_text = text;
			this->_children.append(tmp);
		}
		return this;		
	}

	Tag* Tag::appendTo(Tag *item)
	{
		if(this == NULL)
			return NULL;
		if(item != NULL && this->_parent == NULL)
		{
			this->_parent = item;
			item->_children.append(this);
		}
		return this;
	}
	
	Tag* Tag::html(var text)
	{
		if(this == NULL)
			return NULL;
		this->_deleteChildren();
		this->append(text);
		return this;
	}
	
	var Tag::html()
	{
		if(this == NULL)
			return NULL;
		var html = "";
		if(this->_name == TEXT)
			html += this->_text;
		else
		{
			html += TagDelimiter[this->_type][0];
			html += labelTag[this->_name];
			if(this->_name !=  COMMENT)
			{
				for(unsigned i = 0; i < this->_attrList.count(); i++)
				{
					html = html + " " + this->_attrList.at(i)->name() + "=\"" + this->_attrList.at(i)->value() + "\"";
				}
			}
			html += TagDelimiter[this->_type][1];
			if(this->_container)
			{
				for(unsigned i = 0; i < this->_children.size(); i++)
				{
					html += this->_children.at(i)->html();
				}
				html += TagDelimiter[this->_type][2];
				html += labelTag[this->_name];
				html += TagDelimiter[this->_type][3];
			}
		}
		return html;
	}

	var Tag::attr(var name)
	{
		if(this == NULL)
			return NULL;
		Attr *tmp;
		if((tmp = this->_attrList.find(name)) != NULL)
		{
			return tmp->value();
		}
		return NULL;
	}

	Tag* Tag::attr(var name, var value)
	{
		if(this == NULL)
			return NULL;
		Attr *tmp;
		if((tmp = this->_attrList.find(name)) != NULL)
		{
			tmp->value(value);
		}
		this->_attrList.push(name, value);
		return this;
	}

	Tag* Tag::find(var id)
	{
		if(this == NULL)
			return NULL;
		return this->find("id", id);
	}

	Tag* Tag::find(var attr, var value)
	{
		if(this == NULL)
			return NULL;

		if(this->_attrList.find(attr, value) != NULL)
			return this;
		if(this->_container)
		{
			for(unsigned i = 0; i < this->_children.size(); i++)
			{
				if(this->_children.at(i)->_attrList.find(attr, value) != NULL)
					return this->_children.at(i);
			}
		}
		return NULL;
	}

	Tag* Tag::addClass(var c)
	{
		Attr *tmp = this->_attrList.find(c);
		if(tmp == NULL)
			this->_attrList.push("class", c);
		else
			tmp->value(tmp->value() + " " + c);
		return this;	
	}

	void Tag::_deleteChildren()
	{
		if(this != NULL)
		{
			if(this->_children.size() > 0)
			{
				for(unsigned i = this->_children.size()-1; i >= 0; i--)
				{
					delete this->_children.at(i);
				}
			}
		}
	}

	Tag::~Tag()
	{
		if(this != NULL)
		{
			this->_deleteChildren();
		}
	}

}