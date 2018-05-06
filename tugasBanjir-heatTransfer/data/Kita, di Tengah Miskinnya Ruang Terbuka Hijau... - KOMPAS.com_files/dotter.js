/*
* go go go !
* 24/05/2012
*/
var newsUrl = document.location.href;
var newsTitle = jQuery("meta[property=og:title]").attr('content');
var newsDesc = jQuery("meta[property=og:description]").attr('content');
jQuery(function(){
	
	if(jQuery('#dotterWidget')){
		var maWidget =  jQuery('#dotterWidget');
		
		
		jQuery.getJSON("http://api.kompas.com/2012/4th/index.php/widgetapi?callback=?",{
		  q: newsUrl
		},function(htm) {
			console.log(htm);
			if(htm.status == 'success'){
			
			var dotterHtml  = '<div class="banultah4">\
    	        <div style="padding-right:70px;padding-bottom:10px;">';
			if(htm.is_login == 'true' && htm.is_twitter == 'true'){
					dotterHtml +='<a class="poppoin4" href="#" onclick="mainin(); return false" title="click Disini"></a>';
				}
			if(htm.is_login == 'true' && htm.is_twitter == 'false'){
					dotterHtml +='<a class="poppoin4" href="http://ads2.kompas.com/kompascom4th/index.php/widgetapi?redirect='+newsUrl+'" id="poinpop" title="Anda harus join Twitter Apps kompas4th dahulu"></a>';
				}
				
			if(htm.is_login == 'false' && htm.is_twitter == 'false'){
				dotterHtml +='<a class="poppoin4 fn_login" href="https://login.kompas.com/logins.php?srvc=act&sr=mykompas&done='+newsUrl+'" id="poinpop" title="Anda harus login Mykompas dan join Twitter Apps kompas4th dahulu"></a>';
				}
				
			dotterHtml +='</div>\
        	    <div style="padding-right:80px;" class="temukan4">\
				Temukan lebih banyak lagi untuk menambah poin.' ;
				dotterHtml +='<a href="http://ads2.kompas.com/kompascom4th" target="_blank" >Cara bermain ada di sini</a></div>';
				maWidget.html(dotterHtml);
	        
			}
		});
		
		jQuery('#poinpop').live('click',function(){
			checkCookie();
		});
		
		
	}

});
function mainin(){
		jQuery.getJSON("http://api.kompas.com/2012/4th/index.php/widgetapi?callback=?",{
		  main: 'ok',
		  uri :newsUrl,
		  title:newsTitle,
		  desc:newsDesc,
		},function(htm) {
			if(htm.msg == 'sudah'){
				alert('Berita ini sudah terdaftar di orangeDotter mission Anda, silahkan melanjutkan pencarian berita selanjutnya.');
				return false;
			}else{
				jQuery.fancybox({
					'width': '56%',
					'height': '54%',
					'autoScale': true,
					'transitionIn': 'fade',
					'transitionOut': 'fade',
					'type': 'iframe',
					'href': 'http://api.kompas.com/2012/4th/index.php/widgetapi/point'
				});
			}
			
		});
}
function checkCookie()
{
var token=getCookie("IFA");
  if (token!=null && token!="")
  {
	jQuery.getJSON("http://api.kompas.com/2012/4th/index.php/widgetapi?callback=?",{
		  checktwit: 'ok'
		},function(htm) {
			console.log(htm);
			var kompasEmail =  htm.data.user_email;
			
		});
  }
else 
  {
	console.log('login');
	jQuery('.fn_login').click();
  }
}

function getCookie(c_name)
{
var i,x,y,ARRcookies=document.cookie.split(";");
for (i=0;i<ARRcookies.length;i++)
{
  x=ARRcookies[i].substr(0,ARRcookies[i].indexOf("="));
  y=ARRcookies[i].substr(ARRcookies[i].indexOf("=")+1);
  x=x.replace(/^\s+|\s+$/g,"");
  if (x==c_name)
    {
    return unescape(y);
    }
  }
}