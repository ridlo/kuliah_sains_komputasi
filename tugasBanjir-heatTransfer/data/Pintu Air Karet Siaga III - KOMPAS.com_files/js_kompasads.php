//s-intextad
function findPos(obj) {
	var curleft = curtop = 0;
	if (obj.offsetParent) {
		curleft = obj.offsetLeft
		curtop = obj.offsetTop
		while (obj = obj.offsetParent) {
			curleft += obj.offsetLeft
			curtop += obj.offsetTop
		}
	}
	return [curleft,curtop];
}

//Display a named menu, at the position of another object
function display_menu(parent,named)
{
	//get the named menu
	var menu_element = document.getElementById(named);
	//override the 'display:none;' style attribute
	menu_element.style.display = "";
	//get the placement of the element that invoked the menu...
	var placement = findPos(parent);
	//...and put the menu there
	menu_element.style.left = placement[0] + 50 + "px";
	menu_element.style.top = placement[1] - 240 + "px";
}

//Hide a named menu
function hide_menu(named)
{
	//get the named menu
	var menu_element = document.getElementById(named);
	//hide it with a style attribute
	menu_element.style.display = "none";
}
//e-intex ad

function popUpBanner(urlTarget, windowTarget, widowTitle,windowProperties)
{
	var remote = null;
	remote = window.open('', widowTitle, windowProperties);
	if (remote != null) {
		if (remote.opener == null) remote.opener = windowTarget;
			remote.location.href = urlTarget;
		}
	}

	var ns4 = (document.layers); 
	var ie4 = (document.all && !document.getElementById); 
	var ie5 = (document.all && document.getElementById); 
	var ns6 = (!document.all && document.getElementById); 

function attach(id) { 
	var obj 
	if(ns4) obj = document.layers[id]; 
	else if(ie4) obj = document.all[id]; 
	else if(ie5 || ns6) obj = document.getElementById(id); 
		return obj 
	} 

function showbanner(parentId, childId){
	parentlayer = attach(parentId); 
	childlayer = attach(childId); 
	parentlayer.style.visibility = "hidden"; 
	childlayer.style.visibility = "visible";
}
function showbannersamsung(childId){
	childlayer = attach(childId); 
	//parentlayer.style.visibility = "visible"; 
	childlayer.style.visibility = "visible";
}
function hidebanner(parentId, childId){
	parentlayer = attach(parentId); 
	childlayer = attach(childId); 
	parentlayer.style.visibility = "visible"; 
	childlayer.style.visibility = "hidden"; 
}

// *** Show/hide layer
function MM_showHideLayers() { //v9.0
	var i,p,v,obj,args=MM_showHideLayers.arguments;
	for (i=0; i<(args.length-2); i+=3)
	with (document) if (getElementById && ((obj=getElementById(args[i]))!=null)) { v=args[i+2];
		if (obj.style) { obj=obj.style; v=(v=='show')?'visible':(v=='hide')?'hidden':v; }
		obj.visibility=v; }
}

;(function($) {
	$(function() {
	
		// *** Show/hide banner
		$('#x').mouseover(function() {
			showbanner('x', 'y', 1);
		});
		$('#y').mouseout(function() {
			hidebanner('x', 'y', 0);
		});
		
		$('#x2').mouseover(function() {
			showbanner('x2', 'y2', 1);
		});
		$('#y2').mouseout(function() {
			hidebanner('x2', 'y2', 0);
		});
		$('#a2').mouseover(function() {
			showbanner('b2', 'b2', 1);
		});
		$('#a2').mouseout(function() {
			hidebanner('a2', 'b2', 0);
		});
		
		// *** Banner bottom overlay
		$('#bannerclose').live('click', function(e) {
			if(e.button == 0) {
				$('#tb').slideToggle(250);
				return false;
			}
		});
		
		// *** Banner bottom overlay
		$('#closebca').live('click', function(e) {
			if(e.button == 0) {
				$('#topbar1').remove();
				return false;
			}
		});
		
		// *** Banner marlboro
		$('#closemrr').live('click', function(e) {
			if(e.button == 0) {
				$('#floating_malboro').remove();
				return false;
			}
		});
		
		// Banner top2 expand/normal
		/*$('#top2_normal').mouseover(function() {
			MM_showHideLayers('top2_expand','','show','top2_normal','','hide');
		});
		$('#top2_expand div').mouseout(function() {
			MM_showHideLayers('top2_expand','','hide','top2_normal','','show');
		});*/
		
		// *** Stick the banner :)
		if(typeof(banner) != 'undefined') {
			for(var pos in banner) {
				if($('#banner_' + pos).length) {
					$('#banner_' + pos).prepend(banner[pos]);
				}
			}
		}
		
		// *** On-text banner
		$("div.panel_button").click(function(){										 
			$("div#droppanel").animate({
				height: "60px"
			})
			$("div.panel_button").toggle();	
		});		
	   $("div#hide_button").click(function(){
			$("div#droppanel").animate({
				height: "0px"
			}, 0);	
	   });		

	
	});
})(jQuery);
