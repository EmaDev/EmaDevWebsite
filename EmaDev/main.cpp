#include "main.h"

Server *server;
Dom *dom;
Json *json;

static void debug(int timeout)
{
	timeout *= 1000;
	timeout += clock(); 
	while(clock() < timeout)
		continue;				// BREAKPOINT HERE FOR DEBUG
}

int main(int argc, char ** argv, char **envv)
{
	Server s = Server(envv);
	server = &s;
	dom = server->html;
	json = server->json;

	if(server->request->get("debug") == 1) debug(20);

	bool isJson = false;
	try
	{
		server->initSql("budget2");
		if(server->request->get("json") == 1)
		{
			server->setRenderType(RENDER_JSON);
			isJson = true;
		}
		else
		{
			server->setRenderType(RENDER_HTML);
			graphicInit();
		}

		if(isJson)
		{
			parseJsonPage();
		}
		else
		{
			parseHtmlPage();
		}
	}
	catch(SqlException &ex)
	{
		if(isJson)
		{
			json->setStatus(false,"Sql Error : " + ex.message() + " - State : " + ex.state());
		}
		else
		{
			dom->find("body")->html("Sql Error : " + ex.message() + " - State : " + ex.state());
		}
	}

	cout<<server->render();

	return 0;
}
















/*

s.setDefaultHeader(RENDER_HTML);
	Dom *dom = s.html;
	try
	{
		Sql *sql = new Sql("budget2");
		Select *s = sql->select();
		
		s->value("azienda")->value("budget_id")
		->from("bu_budget");


		dom->find("body")->append( "Eseguo query : " + s->getSql() );

		s->exec();
		while(s->fetch())
		{
			dom->find("body")->append(
				(new Tag(P))->html( " Budget id : " + s->get("budget_id") + " Azienda : " + s->get("azienda"))
			);
		}
	}
	catch(SqlException &ex)
	{
		dom->find("body")->html("Sql Error : " + ex.message() + " - State : " + ex.state());
	}


*/