jQuery.getJSON('http://api.kompas.com/widget/forum/'+rubrik+'/'+limit+'?jsoncallback=?',function(data){
	jQuery('#my_forum').html(data.data);
});