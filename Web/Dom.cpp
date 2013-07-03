#include "Web.h"
#include "Dom.h"

namespace Web
{
	
	Dom::Dom()
	{
		this->_html = new Tag(HTML);
		this->_head = (new Tag(HEAD))->attr("id","head");
		this->_body = (new Tag(BODY))->attr("id","body");
		_html->append(_head)->append(_body);
	}
	Dom::~Dom()
	{
		
	}
	Dom* Dom::append(Tag *item)
	{
		this->_body->append(item);
		return this;
	}
	Dom* Dom::append(var text)
	{
		this->_body->append(text);
		return this;
	}
	Dom* Dom::html(var text)
	{
		this->_body->html(text);
		return this;
	}
	var Dom::attr(var name)
	{
		return this->_html->attr(name);
	}
	Dom* Dom::attr(var name, var value)
	{
		this->_html->attr(name, value);
		return this;
	}
	Tag* Dom::find(var id)
	{
		return this->_html->find(id);
	}
	Tag* Dom::find(var attr, var value)
	{
		return this->_html->find(attr, value);
	}
	Dom* Dom::addClass(var c)
	{
		this->_html->addClass(c);
		return this;
	}
	var Dom::html()
	{
		return this->_html->html();
	}
	var Dom::title()
	{
		return this->_head->find("title") || "";
	}
	Dom *Dom::title(var t)
	{
		Tag *tt = this->_head->find("title");
		if(tt == NULL)
		{
			tt = new Tag(TITLE);
			tt->html(t)->attr("id","title");
			this->_head->append(tt);
		}
		else
		{
			tt->html(t);
		}
		return this;
	}
	Dom *Dom::addScriptFile(string url)
	{
		this->_head->append(
			(new Tag(SCRIPT))->attr("src",url)->attr("type","text/javascript")
		);
		return this;
	}
	Dom *Dom::addCssFile(string url)
	{
		this->_head->append(
			(new Tag(LINK))->attr("href",url)->attr("type","text/css")->attr("rel","stylesheet")
		);
		return this;
	}
}