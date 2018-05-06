
function getPage(inUrl) {
  inUrl = inUrl.replace("www.",'');
  if (inUrl.charAt(inUrl.length-1) == '/') {
    return inUrl.slice(0,inUrl.length-1);
  } else {
    return inUrl;
  }
}

function loadJSON(url) {
  var headID = document.getElementsByTagName("head")[0];
  var newScript = document.createElement('script');
  newScript.type = 'text/javascript';
  newScript.src = url;
  headID.appendChild(newScript);
}
function updateMeta(keywords_in_JSON){
  if (keywords_in_JSON.keywordslen > 0) {

    var metatags=document.getElementsByTagName("head")[0].getElementsByTagName("meta");
    var metalength = metatags.length;
    idx = -1;
    for (i=0;i<metalength;i++)
    {
      if (metatags[i].name.toLowerCase() == "keywords") {
        idx = i;
        break;
      }
    }
    if (idx == metalength || idx == -1) {
      var metaRdf = document.createElement("meta");
      metaRdf.setAttribute("name", "keywords");
      metaRdf.setAttribute("content", keywords_in_JSON.keywords);
      document.getElementsByTagName("head")[0].appendChild(metaRdf);
    } else {
      var metaRdf = metatags[idx];
      var curkeywords = metaRdf.getAttribute("content");
      if (curkeywords.charAt(curkeywords.length-1) == ',') {
          curkeywords = curkeywords.substring(0,curkeywords.length-1);
      }
      metaRdf.setAttribute("content", curkeywords + "," + keywords_in_JSON.keywords);
    }
  }
}
//
//var websparam = escape(getPage(window.location.href));
//
//var url = "http://app.sittiapis.com/getKeyword.php";
//loadJSON(url + "?webs=" + websparam + "&type=JSON&callback=updateMeta&ms=" + new Date().getTime());
