;(function ( $, window, document, undefined ) {
    var pluginName = 'liveFunction',
        obj = new Array();

    function plugin( _selector, _method , _function ) {
    	check_params(_selector, _method, _function);
    	var new_obj = { "selector" : _selector, "method" : _method , "function" : _function  };
		obj.push( new_obj );
		update();
        return this;
    };
    
    var update = function()
    {
    	$.each(obj,function(index, item)
    	{
    		$(item.selector).each(function(i, elem)
    		{
    			if(!$(elem).data("ready"))
    			{
    				$(elem).data("ready",new Array());
    			}
    			var found = false;
    			$.each($(elem).data("ready"), function(bind_index, bind_elem)
    			{
    				if(bind_elem == item)
    				{
    					found = true;
    				}
    			});
    			if(!found)
    			{
    				$(elem).data("ready").push(item);
    				$(elem).bind(item.method,item["function"]);
    			}
    		});
    	});
    }
    var check_params = function( _selector, _method , _function )
    {
    	if($.type(_selector) != "string")
    		throw "Selector parameter isn't a string object.";
    	if($.type(_method) != "string")
    		throw "Method parameter isn't a string object.";
    	if($.type(_function) != "function")
    		throw "Function parameter isn't a function object.";
    }
    window[pluginName] = plugin;
    window[pluginName].count = function()
    {
    	return obj.length;
    }
    window[pluginName].update = function()
    {
    	update();
    }
    $.fn[pluginName] = function( _method , _function)
	{
		window[pluginName].call(this, this.selector, _method, _function);
	}
})( jQuery, window, document );