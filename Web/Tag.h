#pragma once

#include "Web.h"

using namespace std;

namespace Web{
		
	enum TAG_NAME{
		TAG_DELIMITER_BLOCK, 
		HTML,
		HEAD,
		BODY,
		DIV,
		P,
		TITLE,
		LINK,
		SCRIPT,
		SPAN,
		HEADER,
		H1,
		H2,
		H3,
		H4,
		H5,
		H6,
		FORM,
		FIELDSET,
		LEGEND,
		TABLE,
		TBODY,
		THEAD,
		TFOOT,
		TR,
		TH,
		TD,
		LABEL,
		SELECT,
		OPTION,
		TAG_DELIMITER_INLINE,
		IMG,
		CANVAS,
		META,
		HR,
		INPUT,
		TAG_DELIMITER_SPECIAL,
		DOCTYPE,
		COMMENT,
		TEXT
	};
	enum TAG_TYPE{
		TAG_TYPE_BLOCK,
		TAG_TYPE_INLINE,
		TAG_TYPE_SPECIAL
	};

	class Tag
	{
	public:
		Tag(TAG_NAME name); 
		Tag* append(Tag *item);
		Tag* append(var text);
		Tag* appendTo(Tag *item);
		Tag* html(var text);
		var attr(var name);
		Tag* attr(var name, var value);
		Tag* find(var id);
		Tag* find(var attr, var value);
		Tag* addClass(var c);
		var html();

		~Tag();

	private:
		var _text;
		bool _container;
		Tag* _parent;
		void _deleteChildren();
		List<Tag *> _children;
		TAG_NAME _name;
		TAG_TYPE _type;
		AttrList _attrList;
	};

}