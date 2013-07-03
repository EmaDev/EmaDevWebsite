#pragma once

#include "Web.h"

using namespace std;


namespace Web
{
	class Dom
	{
	public:
		Dom();
		~Dom();
		Dom* append(Tag *item);
		Dom* append(var text);
		Dom* html(var text);
		var attr(var name);
		Dom* attr(var name, var value);
		Tag* find(var id);
		Tag* find(var attr, var value);
		Dom* addClass(var c);
		var html();
		var title();
		Dom *title(var t);
		Dom *addScriptFile(string url);
		Dom *addCssFile(string url);
	private:
		Tag *_html;
		Tag *_head;
		Tag *_body;
	};
}