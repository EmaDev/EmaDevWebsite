#include "main.h"

bool parseHtmlPage()
{
	Tag *content = dom->find("page");
	if(server->request->get("page") == "anagrafica")
	{
		dom->title("Euresys || Anagrafica");
		content->append(
			(new Tag(FORM))->append(
				(new Tag(FIELDSET))->append(
					(new Tag(LEGEND))->html("Gestione Anagrafica")
				)->append(
					(new Tag(TABLE))->append(
						(new Tag(TBODY))->append(
							(new Tag(TR))->append(
								(new Tag(TD))->append(
									(new Tag(TABLE))->append(
										(new Tag(TR))->append(
											(new Tag(TD))->append(
												tag_gruppi_anagrafici("gruppi_anag")
											)->append(
												(new Tag(SELECT))->attr("name","select_operator")->attr("style","margin-left:10px")->append(
													(new Tag(OPTION))->attr("value",1)->html("=")
												)->append(
													(new Tag(OPTION))->attr("value",2)->html("!=")
												)->append(
													(new Tag(OPTION))->attr("value",3)->html("&gt;")
												)->append(
													(new Tag(OPTION))->attr("value",4)->html("&lt;")
												)->append(
													(new Tag(OPTION))->attr("value",5)->html("&gt;=")
												)->append(
													(new Tag(OPTION))->attr("value",6)->html("&lt;=")
												)
											)
										)
									)->append(
										(new Tag(TR))->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("placeholder","Filtro su Nome/Cognome")->attr("size",50)
											)
										)
									)
								)
							)->append(
								(new Tag(TD))->append(
									(new Tag(TABLE))->append(
										(new Tag(TR))->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Data di assunzione")->addClass("title")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Da")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "assunzione_inizio")->addClass("datapiker")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("A")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "assunzione_fine")->addClass("datapiker")
											)
										)
									)->append(
										(new Tag(TR))->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Data di cessazione")->addClass("title")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Da")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "cessazione_inizio")->addClass("datapiker")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("A")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "cessazione_fine")->addClass("datapiker")
											)
										)
									)/*->append(
										(new Tag(TR))->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Età")->addClass("title")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("Da")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "eta_inizio")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(LABEL))->append("A")
											)
										)->append(
											(new Tag(TD))->append(
												(new Tag(TAG_NAME::INPUT))->attr("type","text")->attr("name", "eta_fine")
											)
										)
									)*/
								)
							)
						)
					)
				)
			)
		);
	}
	else
	{
		dom->title("Euresys || 404");
		content->append(
			(new Tag(P))->html("404. Page not found")
		);
	}
	return true;
}

bool parseJsonPage()
{
	if(server->request->get("page") == "home")
	{
		
	}
	else
	{
		json->setStatus(false,"Page not found");
	}
	return true;
}