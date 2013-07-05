#include "Web.h"
#include "Response.h"

namespace Web
{
	Server::Server(char **env)
	{
		this->html = new Dom();
		this->json = new Json();
		this->request = new Request(env);
		this->response = new Response();
		this->_renderType = RENDER_HTML;
		this->_header = new AttrList();
	}
	Server::~Server()
	{
		delete this->html;
		delete this->json;
		delete this->request;
		delete this->response;
		delete this->_header;
	}
	Server *Server::setRenderType(RenderType rt)
	{
		this->_renderType = rt;
		this->setDefaultHeader(rt);
		return this;
	}
	RenderType Server::getRenderType()
	{
		return this->_renderType;
	}
	Server *Server::addHeader(var name, var value)
	{
		this->_header->push(name, value);
		return this;
	}
	Server *Server::setDefaultHeader(RenderType renderType)
	{
		this->_header->clear();
		switch(renderType)
		{
		case RENDER_HTML:
			this->_header->push("Content-Type","text/html; charset=UTF-8");
			break;
		case RENDER_JSON:
			this->_header->push("Content-Type","application/json");
			break;
		}
		return this;
	}
	var Server::render()
	{
		var render = "";
		for(unsigned int i = 0; i < this->_header->count(); i++)
		{
			render = render + this->_header->at(i)->name() + ":" + this->_header->at(i)->value() + "\n";
		}
		render = render + this->response->renderCookie();
		render = render + "\n";
		if(this->_renderType == RENDER_HTML)
		{
			render = render + "<!doctype html>" + this->html->html();
		}
		else if(this->_renderType == RENDER_JSON)
		{
			//render = render + this->json->render();
		}
		return render;
	}
	Server *Server::initSql(var DSN)
	{
		this->sql = new Sql(DSN);
		return this;
	}
}