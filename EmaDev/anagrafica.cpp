#include "main.h"

Tag * tag_gruppi_anagrafici(var id)
{
	Tag *s = (new Tag(SELECT))->attr("id",id);
	Select *select = server->sql->select();
	select->value("descrizione")->value("gruppo")
		->from("gruppi_anag")
		->order("gruppo", ASC)->exec();

	while(select->fetch())
	{
		s->append(
			(new Tag(OPTION))->attr("value", select->get("gruppo"))
			->html("( " + select->get("gruppo") + " ) " + select->get("descrizione"))
		);
	}
	return s;
}