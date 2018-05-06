jQuery.noConflict();
(function($) {
	$.fn.extend({
		kompasArtbox: function(params) {
			var obj = $(this);
			var defaultParams = {
				siteno			: 	"",
				sectionid		: 	"",
				articleid		: 	"",
				nameutm			:	"",
				nameid			:	"",
				prevpermalink		:	"",
				keywords		:	"",
				tanggal			:	""
			};
			
			params = $.extend({}, defaultParams, params);
			
			$.ajax({
				url		: 	"http://api.kompas.com/2012/artbox/api/article?jsoncallback=?",
				type		: 	"GET",
				dataType	: 	"jsonp",
				data		: 	{
								"siteno" 		: 	params.siteno, 
								"sectionid" 		: 	params.sectionid,
								"articleid"		: 	params.articleid,
								"nameutm"		:	params.nameutm,
								"nameid"		: 	params.nameid,
								"prevpermalink"		:	params.prevpermalink,
								"keywords"		:	params.keywords,
								"tanggal"		: 	params.tanggal
							},
				global		: 	false,
				success		: 	function (data) {
									obj.html(data.result);
								},
				error		: 	function (xhr, msg, obj) {
									alert ("Error occured. Try Again!");
							}
			});
		}
	});
	
})(jQuery);