(function($){

	//plugin name - kompasComment
    $.fn.kompasComment = function(options) {

		options = $.extend ({}, $.fn.kompasComment.defaults, options);

		$.fn.kompasComment.options = options;

		var loader_img = '<img src="http://stat.k.kidsklik.com/data/2k11/comment/images/ajax-loader.gif" />';

		return this.each (function() {
			var o = options;
			o.increment = +o.increment;

			if (o.stat_counter != null) {
				$(o.stat_counter).html (loader_img);
				var url_article=document.URL;
				//var url_article='http://properti.kompas.com/index.php/read/2012/06/19/15543972/Kita..di.Tengah.Miskinnya.Ruang.Terbuka.Hijau....';

				var extra_param = ''
				if (o.increment) {
					extra_param = '&increment='+o.increment
						+'&title='+escape(document.title)
						+'&url='+url_article
					;
				}

				$.getJSON(
					'http://srv.kompas.com/statapi/stat/count?jsoncallback=?'
					+'&app_id='+o.app_id+'&article_id='+o.article_id
					+'&format=json'
					+'&url='+url_article
					+extra_param,
					function(data) {
					var totalRead = 0;
					if (data.status) {
						totalRead = data.result;
					}
					$(o.stat_counter).html (totalRead);
					//console.log (data);
				});

				/*-- Ambil counter dari Edo via ajax --*/
				/*-- NOTES: diganti jadi via controllers stat/count --*/
				//var edo_encoded_url = url_article;
				//edo_encoded_url = edo_encoded_url.replace(/\//g, "|-|");
				//edo_encoded_url = edo_encoded_url.replace(/\#/g, "");
				//edo_encoded_url = encodeURIComponent (edo_encoded_url);
				//$.getJSON(
				//	'http://api.kompas.com/data/getreadcounter/'+ o.article_id +'/'
				//	+ edo_encoded_url
				//	+ '?jsoncallback=?'
				//	, function (data) {
				//		var totalRead = 0;
				//		if (data.status) {
				//			totalRead = data.results[0].ReadCount;
				//		}
				//		$(o.stat_counter).html (totalRead);
				//		//console.log (data);
				//	}
				//);
			}

			if (o.comment_counter != null) {
				// cuma menampilkan loading image, loading jumlah komentarnya nanti dibawah
				$(o.comment_counter).html (loader_img);
			}


			// Assign current element to variable, in this case is ID of the
			// comment placeholder
			var obj = $(this);

			obj.html ('<div align="center">'+loader_img+'</div>');

			// get listing comment via AJAX
			setTimeout (
				function () {
					$.ajax ({
						  url: 'http://srv.kompas.com/commentapi/comment/listing?jsoncallback=?'
						, dataType: 'jsonp'
						, data: {
							  app_id:		o.app_id
							, article_id:	o.article_id
							, how_many:		o.how_many
							, html:			o.html
							, page:			o.page
							, force:		o.force
						}
						, global: false
						, beforeSend: function () {
						}
						, success: function (data) {
							obj.html (data.result);
							//console.log (data);
							output = data;
							/*--if (data.status) {
								obj.html (data.result);
							} else {
								alert (data.error);
								obj.html (data.error);
							}--*/

							if (o.comment_counter != null) {
								$(o.comment_counter).html (loader_img);
								if (data.total_records) {
									$(o.comment_counter).html (data.total_records);
								} else {
									$(o.comment_counter).html ('-');
								}
							}

						}
						, error: function (xhr, msg, obj) {
							alert ("An error occured: " + msg + "\nPlease try again");
						}
					});
					//get current URL


					/*--if (o.comment_counter != null) {
						$(o.comment_counter).html (loader_img);
						$.getJSON('http://srv.kompas.com/commentapi/comment/count?jsoncallback=?&app_id='+o.app_id+'&article_id='+o.article_id+'&format=json', function(data) {
							var totalComment = 0;
							if (data.status) {
								totalComment = data.result;
							}
							$(o.comment_counter).html (totalComment);
							//console.log (totalComment);
						});
					}--*/

				},
				500
			);

		});
	}


	//Settings list and the default values
	$.fn.kompasComment.defaults = {
		  app_id: 1
		, article_id_: 1
		, how_many: 5
		, html: 1
		, page: 1
		, force: 0
		, comment_counter: null
		, stat_counter: null
		, increment: false
	};

	//user defined settings
	$.fn.kompasComment.options = {};

})(jQuery);
