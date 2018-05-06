// JavaScript Document
jQuery.noConflict();
function zone_counter(zone_id,sec_id){
	//var api_url_count = 'http://' + document.domain + '/api/zone_count';
	var api_url_count = 'http://' + document.domain + '/api/zone_count';
	jQuery.post(api_url_count, { zoneid:zone_id, secid:sec_id });
}
