
//  This version of the refresh function will cause a new
//  entry in the visitor's history.  It is provided for
//  those browsers that only support JavaScript 1.0.
//  This is only for the redirect.

var sURL = unescape(window.location.href);
var edittable = null;
var previewListing = null;
var inPopUp;

function windowClose(windowname)
{
	if (windowname && windowname.open && !windowname.closed) windowname.close();
}


function tablePopUpLg(link)
{
	windowClose(previewListing);
	previewListing = window.open(link,'_previewListing','toolbar=no,width=725,height=500,resizable=no,scrollbars=yes');
	previewListing.focus();
	if (inPopUp) self.close();
}

function tablePopUp(link)
{
	windowClose(edittable);
	edittable = window.open(link,'_edittable','toolbar=no,width=550,height=550,resizable=yes,scrollbars=yes');
	edittable.focus();
	if (inPopUp) self.close();
}

function tablePopUp1(link, height, width){
	windowClose(edittable);
	edittable = window.open(link,'_edittable','toolbar=no,width=' + width + ',height=' + height + ',resizable=no,scrollbars=yes');
	edittable.focus();
	if (inPopUp) self.close();
}

function tablePopUpAdjust(link, height, width)
{
	if(width<=550){width=550;}
	if(height<=350){height=350;}
	windowClose(edittable);
	edittable = window.open(link,'_edittable',"toolbar=no,width=" + width + ",height=" + height + ",resizable=no,scrollbars=yes");
	edittable.focus();
	if (inPopUp) self.close();
}

function MM_swapImage() { //v3.0
  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
}
function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_preloadImages() { //v3.0
 var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
   var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
   if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_findObj(n, d) { //v4.0
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && document.getElementById) x=document.getElementById(n); return x;
}
//-->
