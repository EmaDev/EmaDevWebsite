#include <iostream>
#include <stdio.h>
#include <string>

#include "Web.h"

using namespace std;
using namespace Web;


void parsePage()
{
	
}


int main(int argc, char ** argv, char **envv)
{
	Server s = Server(envv);
	Dom *dom = s.html;
	Json *json = s.json;

	bool isJson = false;
	try
	{
		s.initSql("budget2");
		if(s.request->get("json") == 1)
		{
			s.setRenderType(RENDER_JSON);
			isJson = true;
		}
		else
		{
			s.setRenderType(RENDER_HTML);
		}

		if(isJson)
		{
			
		}
		else
		{
			
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

	cout<<s.render();

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