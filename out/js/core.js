$(document).ready(function()
{

	$.datepicker.setDefaults($.datepicker.regional['it']);
	window.init = function()
	{
		$(".datapiker").not(".ready").each(function(index, elem)
		{
			$(elem).attr("size",10).datepicker({
				onClose: function( selectedDate ) {
					if($(elem).attr("data-min-of"))
					{
						$.each($(elem).attr("data-min-of").split(","), function(index, value)
						{
							var elemDest = $(elem).closest("form").find("*[name='"+ value +"']");
							elemDest.datepicker( "option", "minDate", selectedDate );
						});
					}
					if($(elem).attr("data-max-of"))
					{
						$.each($(elem).attr("data-max-of").split(","), function(index, value)
						{
							var elemDest = $(elem).closest("form").find("*[name='"+ value +"']");
							elemDest.datepicker( "option", "maxDate", selectedDate );
						});
					}
				}
			});
		});
	}
	init();
});