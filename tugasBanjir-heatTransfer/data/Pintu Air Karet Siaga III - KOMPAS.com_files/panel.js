
(function($){$.getJSON('http://api.my.kompas.com/panel/template/?app_id=kompascom&app_key=k01sbbdjweri938X&jsoncallback=?',function(data){if(data&&data.template){if(data.is_banned){}
if($('div.top_bar').length){$('div.top_bar').slideUp('100',function(){$(this).replaceWith(data.template);$(this).slideDown('100');});}
else{$('body').animate({'padding-top':'36px'},'fast');$('body').prepend(data.template);}}});window.reloadWindow=function()
{window.location.href=window.location.href;}})(jQuery);