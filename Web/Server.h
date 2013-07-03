#pragma once

#include "Web.h"

using namespace std;

namespace Web
{
	enum RenderType { RENDER_HTML, RENDER_JSON };

	class Server
	{
	public:
		Server(char **env);
		~Server();
		Server *setRenderType(RenderType rt);
		RenderType getRenderType();
		var render();
		Server *addHeader(var name, var value);
		Server *setDefaultHeader(RenderType renderType);
		Dom *html;
		//Json *json;
		Request *request;
		Response *response;
	private:
		AttrList *_header;
		RenderType _renderType;
	};
}