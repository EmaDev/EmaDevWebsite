#include <iostream>
#include <stdio.h>
#include <string>

#include "Web.h"

using namespace std;
using namespace Web;


int main(int argc, char ** argv, char **envv)
{
	Server s = Server(envv);
	s.setDefaultHeader(RENDER_HTML);
	Dom *dom = s.html;
	try
	{
		Sql *sql = new Sql("budget2");
		Select *s = sql->select();
		s->value("budget_id")->value("azienda")->from("bu_budget")->order("budget_id", DESC);
		s->exec();
		while(s->fetch())
		{
			dom->find("body")->append(
				(new Tag(P))->html("Budget id : " + s->get("budget_id") + " Azienda : " + s->get("azienda"))
			);
		}
	}
	catch(SqlException &ex)
	{
		dom->find("body")->html("Sql Error : " + ex.message() + " - State : " + ex.state());
	}

	cout<<s.render();

	return 0;
}
