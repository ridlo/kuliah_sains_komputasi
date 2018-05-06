// JavaScript Document

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



function checkCookie()
{
var username=getCookie("ExplainCookie");
if (username!=null && username!="")
  {
  document.getElementById('alerttop').style.display='none';
  }
  else
   {
  document.getElementById('alerttop').style.display='block';
  }
}

function closemessage()
{
document.getElementById('alerttop').style.display='none';
 var cookievalue ="ExplainCookie=explained;expires="
 var today = new Date();
 var expirestring = new Date();
 expirestring.setTime(today.getTime() + 3600000*24*3500);
 var expirestringtime = expirestring.toUTCString();
document.cookie = cookievalue + expirestringtime +"; path=/"; 
}