#include "main.h"

void graphicInit()
{

	dom->find("head")->append(
		(new Tag(META))->attr("charset","iso-8859-1")
	)->append(
		(new Tag(META))->attr("id", "description")->attr("name", "description")->attr("content", "")
	);

	dom->title("Euresys");
	dom->addCssFile("css/reset.css");
	dom->addCssFile("css/main.css");
	dom->addCssFile("css/smoothness/jquery-ui-1.9.2.custom.min.css");

	dom->addScriptFile("//ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js");
	dom->addScriptFile("js/plugin.js");
	dom->addScriptFile("js/core.js");
	dom->addScriptFile("js/jquery-ui-1.9.2.min.js");
	dom->addScriptFile("js/jquery.ui.datepicker-it.js");

	dom->append(
		(new Tag(DIV))->attr("id","wrapper")->append(
			(new Tag(HEADER))->attr("id", "header")->append(
				(new Tag(DIV))->addClass("wrapper-center")->attr("id","header-content")->append(
					(new Tag(IMG))->attr("id", "logo")->attr("src", "images/ip_logo.png")->attr("alt", "")->attr("title", "infopoint")
				)->append(
					(new Tag(DIV))->attr("id", "version-box")->addClass("inset-box")->html("V. 1.0.0.1")
				)->append(
					(new Tag(DIV))->attr("id","box-user-info")->append(
						(new Tag(IMG))->attr("id","logout")->attr("id","logout")->attr("src", "images/logout.png")->attr("alt", "")->attr("title", "logout")
					)->append(
						(new Tag(DIV))->attr("id","user-info")->html("COSIMA FLORE")->addClass("inset-box")
					)
				)
			)	
		)->append(
			(new Tag(DIV))->addClass("wrapper-center")->append(
				(new Tag(DIV))->attr("id", "page")
			)
		)
	);
}