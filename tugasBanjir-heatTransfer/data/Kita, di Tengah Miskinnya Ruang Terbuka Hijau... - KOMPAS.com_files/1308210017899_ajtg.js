function scanning() {
var keywords;
var metas = document.getElementsByTagName('meta');
for (var x=0,y=metas.length; x<y; x++) {
  if (metas[x].name.toLowerCase() == "keywords") {
    keywords = metas[x];
  }
}
if (keywords==undefined)
{str=window.location.href;}
else
{
var str=keywords.content;
str=(str.replace(/, /gi, ","));}
var title=document.title;
title=(title.replace(/ /gi, ","));
var keyword=title+','+str;
return keyword;
}

function isArray(value) {
	var s = typeof value;
	if (s === 'object') {
		if (value) {
			if (typeof value.length === 'number' && !(value.propertyIsEnumerable('length')) && typeof value.splice === 'function') {
				return true;
			}
		}
	}
	return false;
}

function ajAd(divName) {
	if (isArray(aj_div_tmp) && typeof(aj_content) != 'undefined' && aj_content != null) {
		for (i=0; i<aj_div_tmp.length; i++ ){
			if (aj_div_tmp[i] == divName) {
				document.write(aj_content[i]);				
				break;
			}
		}		
	}
}

////Pop-Up
function ajPostOpen() {
	if (ajwin) {
		if (aj_popunder) {
			ajwin.blur();
		}
	}
}


function standardPopup() {
	if (ajwin == null) {
		ajwin = window.open(ajad, "_blank", ajwinparams);
		ajPostOpen();
	}
}

function clickPopup() {
	if (!aj_popup_onclick_wrnd) {
		return;
	}

	if(window.Event) {
		document.captureEvents(Event.CLICK);
	}
	document.onclick = standardPopup;
}

function iePopup() {
	if (!aj_popup_ie_wrnd) {
		return;
	}
	document.write('<object id="clicksor_xx"' + 
			' classid="clsid:2D360201-FFF5-11d1-8D03-00A0C959BC0A"' + 
			' style="width:1;height:1;top:0;left:0;position:absolute;"' +
			' align="middle"><param name="ActivateApplets" value="1"></object>');
	if (document.getElementById("clicksor_xx")){
		document.getElementById("clicksor_xx").style.width='1';
		document.getElementById("clicksor_xx").style.height='1';

		setTimeout('iePopupCallback();', 1000);
	}
}

function iePopupCallback(){
	try {
		ajwin = document.getElementById("clicksor_xx").DOM.Script.open(ajad, "_blank", ajwinparams);
		ajPostOpen();
	} catch(e) {
	}

	if (ajwin == null) {
		clickPopup();
	}
}

function popup(tag) {
	ajwinparams = "top=0,left=0,width=" + aj_popup_width + ",height=" + aj_popup_height;
	ajad = tag;
	
	ajwin = null;

	standardPopup();
	if (ajwin == null) {
		if (/MSIE/.test(navigator.userAgent)) {
			iePopup();
		} else {
			clickPopup();
		}
	}
}

function param(name, value) {
	if (typeof(value) != 'undefined' && value != "") {
		return name + value;
	}
	
	return "";
}

function pos() {
	if (typeof(aj_pos) == 'undefined') {
		aj_pos = 1;
	} else {
		aj_pos++;
	}
	
	return "&pos="+aj_pos;
}

function pv(aj_pv) {
	if (typeof(aj_pv) != 'undefined' && aj_pv == true) {
		if (typeof(aj_pv_rnd) == 'undefined') {
			aj_pv_rnd = Math.round( (Math.random() + "") * 10000000000000000 ) + 1;
		}
		return "&pv=" + aj_pv_rnd;
	}
	
	return "";
}

if (typeof(aj_server) != 'undefined' && typeof(aj_adspot) != 'undefined' && typeof(aj_zone) != 'undefined') {
	aj_tag = aj_server;

	if (typeof(aj_page) == 'undefined') {
		aj_page = "0";
	}

	if (typeof(aj_pv) == 'undefined' || aj_pv == 'true') {
		aj_pv = true;
	}

	if (typeof(aj_div) != 'undefined' && aj_div != null) {
		view = 'mvj';
	} else if ((typeof(aj_popup_title) != 'undefined' && aj_popup_title != "") || (typeof(aj_fmt) != 'undefined' && aj_fmt == 'iframe')) {
		view = 'vh';
	} else {
		view = 'vj';
	}

	aj_tag += aj_adspot + "/" + aj_page + "/" + view + "?z=" + aj_zone;

	if (typeof(aj_ch) != 'undefined') {
		aj_tag += param("&ch=", aj_ch);
	}
	aj_tag += param("&dim=", aj_dim);

	if (typeof(aj_ct) != 'undefined') {
		aj_tag += param("&ct=", aj_ct);
	}

	aj_tag += pos();

	if (typeof(aj_kw) != 'undefined') {
	aj_kw=scanning();
		aj_tag += param("&kw=", encodeURIComponent(aj_kw));
	}

	var tz = new Date().getTimezoneOffset();
	var url = "";
	try {
	    url = window.top.location.href;
	} catch (err) {
	    url = window.location.href;
	}
	var referrer = document.referrer;

	aj_tag += pv(aj_pv);

	aj_tag += param("&nc=", Math.round( (Math.random() + "") * 100000000 ) + 1);

	if (typeof(aj_click) != 'undefined') {
		aj_tag += param("&click=", aj_click);
	}

	aj_tag += param("&tz=", tz);
	aj_tag += param("&url=", encodeURIComponent(url));
	aj_tag += param("&refer=", encodeURIComponent(referrer));

	if (typeof(aj_popup_title) != 'undefined' && aj_popup_title != "") {
		popup(aj_tag);
	} else if (typeof(aj_fmt) != 'undefined' && aj_fmt == 'iframe' && typeof(aj_width) != 'undefined' && typeof(aj_height) != 'undefined') {
	    var w = ' width="' + aj_width + '"';
	    var h = ' height="' + aj_height + '"';
	    document.write('<iframe scrolling="no" frameborder="0" marginheight="0" marginwidth="0" src="' + aj_tag + '"' + w + h + '></iframe>');
	} else {
		document.write('<'+'scr'+'ipt type="text/javas'+'cript" src="'+aj_tag+'"></'+'scr'+'ipt>');
	}
	if (typeof(aj_div) != 'undefined' && aj_div != null) {	
		aj_div_tmp = aj_div;
		aj_div = undefined;
	}
	if (typeof(aj_page) != 'undefined') {
		aj_page = undefined;
	}
	if (typeof(aj_pv) != 'undefined') {
		aj_pv = undefined;
	}
	if (typeof(aj_server) != 'undefined') {
		aj_server = undefined;
	}
	if (typeof(aj_adspot) != 'undefined') {
		aj_adspot = undefined;
	}
	if (typeof(aj_zone) != 'undefined') {
		aj_zone = undefined;
	}
	if (typeof(aj_tagver) != 'undefined') {
		aj_tagver = undefined;
	}
	if (typeof(aj_dim) != 'undefined') {
		aj_dim = undefined;
	}
	if (typeof(aj_ch) != 'undefined') {
		aj_ch = undefined;
	}
	if (typeof(aj_ct) != 'undefined') {
		aj_ct = undefined;
	}
	if (typeof(aj_kw) != 'undefined') {
		aj_kw = undefined;
	}
	if (typeof(aj_popup_title) != 'undefined') {
		aj_popup_title = undefined;
	}

	if (typeof(aj_width) != 'undefined') {
	    aj_width = undefined;
    }
	if (typeof(aj_height) != 'undefined') {
	    aj_height = undefined;
	}
	if (typeof(aj_fmt) != 'undefined') {
	    aj_fmt = undefined;
	}
}
