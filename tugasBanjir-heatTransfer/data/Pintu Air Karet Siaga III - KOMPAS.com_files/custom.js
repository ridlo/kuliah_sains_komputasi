(function($) {
	$(function() {
		$.extend({
			mySubmitComment: function(article_id,curToken, options) {
				var $t;
				var url_cek_login='http://api.kompas.com/widget/is_loggedin?jsoncallback=?';
				var defaults = {
					my_comment: '#my_comment_content',
					my_comment_info: '#my_comment_info',
					info_error: 'Mohon maaf, harap ulangi kembali.<br />',
					info_success: 'Terima kasih, komentar Anda telah kami terima.<br />',
					info_vote_error: 'Mohon maaf, harap ulangi kembali vote suka komentar ini',
					info_vote_success: 'Terima kasih, vote suka komentar ini telah kami terima',
					info_vote_already: 'Anda sudah pernah vote suka komentar ini',
					info_disvote_error: 'Mohon maaf, harap ulangi kembali vote tidak suka komentar ini',
					info_disvote_success: 'Terima kasih, vote tidak suka komentar ini telah kami terima',
					info_disvote_already: 'Anda sudah pernah vote tidak suka komentar ini',
					reply_comment: '#my_reply_content',
					my_comment_reply: 'a[rel*=my_comment_rpy]',
					my_comment_report: 'a[rel*=my_comment_rpt]',
					my_comment_like: 'a[rel*=my_comment_like]',
					my_comment_dislike: 'a[rel*=my_comment_dislike]'
				};
			
				options = $.extend(defaults, options);
				$(options.my_comment_reply).live('click', function(e) {
					if(e.button == 0) {
						my_user_photo=$('#my_comment_user_photo').attr('src');
						$t = $(this);
						$.getJSON(url_cek_login,{token:curToken}, function(data) {
							if(data.status == 1) {
								var parent_id = $t.attr('id');
								parent_id = parent_id.split('_');
								var block='<li class="sub" id="my_comment_reply_block">';
								block+='<div class="c_left user_komen c_pd_5" align="center">';
								block+='<img src="'+my_user_photo+'"   width="51" height="47"/>';
								block+='<div class="c_biru01_komen c_font12"><a href="#">' + $('#my_comment_user_name').text() + '</a></div>';
								block+='</div>';
								block+='<div class="c_left w_isikomen_sub">';
								block+='<div class="c_font11 komen_list_1">';
								block+='<div class="c_font12 c_lh18">';
								block+='<form action="' + $('#my_comment_form').attr('action') + '" method="post">';
								block+='<input type="hidden" name="my_comment_form_replay_parentid" id="my_comment_form_replay_parentid" value="'+parent_id[3]+'"><div>';
								block+='<textarea cols="40" rows="5" class="form_2 c_w425 h60" name="my_reply_content" id="my_reply_content"></textarea>';
								block+='</div>';
								block+='<div class="pt_10">';
								block+='<button type="button" id="my_comment_reply_submit" class="c_font11 c_pd_5">Submit</button>';
								block+='<button type="reset" class="c_font11 c_pd_5">Reset</button>';
								block+='</div>';
								block+='</form>';
								block+='</div>';
								block+='</div>';
								block+='</div>';
								block+='<div class="c_clearit"></div>';
								block+='</li>';
								if($('#my_comment_reply_block').length) {
									$('#my_comment_reply_block').slideUp('fast', function() {
										$(this).remove();
										if(parent_id[4]==1){
											$t.parents('.w_tool_komen').next().after(block);
										}else{
											$t.parents('li:eq(0)').after(block);
										}
										$('#my_comment_reply_block').css('display', 'none').slideDown('fast', function() {
											//var top = $('#my_comment_reply_block').offset().top;
											//$('html, body').animate({ 'scrollTop': top + 'px' });
										});
									});
								}
								else {
									if(parent_id[4]==1){
										$t.parents('.w_tool_komen').next().after(block);
									}else{
										$t.parents('li:eq(0)').after(block);
									}
									$('#my_comment_reply_block').css('display', 'none').slideDown('fast', function() {

										//var top = $('#my_comment_reply_block').offset().top;
										//$('html, body').animate({ 'scrollTop': top + 'px' });
									});
									
								}
							}
							else {
								$(".fn_login").trigger('click');
			
								//$.sso({bypass: true});
							} 
						});
					}
					return false;
				});
			
				 $(options.my_comment_report).live('click', function(e) {
					if(e.button == 0) {
						$t = $(this);
						$.getJSON(url_cek_login,{token:curToken}, function(data) {
							if(data.status == 1) {
								$t.fancybox({
									'onStart'			: (function(){
										$(this).attr('href',$(this).attr('href')+'/'+curToken);
									}),
									'width'				: 430,
									'height'			: 180,
									'autoScale'			: true,
									'transitionIn'		: 'over',
									'transitionOut'		: 'over',
									'type'				: 'iframe',
									'titleShow'			: false,
									'showNavArrows': false 
								});
								$(options.my_comment_report).trigger('click');
							}else {
								$(".fn_login").trigger('click');
							} 
						});
					}
					return false;
				}); 
				 $(options.my_comment_like).live('click', function(e) {
					if(e.button == 0) {
						$t = $(this);
						$.getJSON(url_cek_login,{token:curToken}, function(data) {
							if(data.status == 1){
								var mcl_id = $t.attr('id');
								mcl_id = mcl_id.split('_');
								$.getJSON('http://api.kompas.com/widget/save_vote?jsoncallback=?',{cid:mcl_id[3],textid:mcl_id[4],type:1}, function(data) {
									if(data.status=1){
										var curtotal=$('#my_comment_like_skor_'+mcl_id[3]+'_'+mcl_id[4]).text();
										if($.cookie('list_id_vote')==null){
											$.cookie('list_id_vote',mcl_id[3]+'_'+mcl_id[4],{ expires: 1 });
											$('#my_comment_like_skor_'+mcl_id[3]+'_'+mcl_id[4]).text(parseInt(curtotal)+1);
											alert(options.info_vote_success);
										}else{	
											var is_exist=0;
											var list_id_vote=$.cookie('list_id_vote');
											data=list_id_vote.split('|');
											$.each(data,function(i,item){
												if(item==mcl_id[3]+'_'+mcl_id[4]){
													is_exist=1;
													return;
												}
											});
											if(is_exist==1){
												alert(options.info_vote_already);
											}else{
												list_id_vote=list_id_vote+'|'+mcl_id[3]+'_'+mcl_id[4];
												$.cookie('list_id_vote',list_id_vote,{ expires: 1 });
												$('#my_comment_like_skor_'+mcl_id[3]+'_'+mcl_id[4]).text(parseInt(curtotal)+1);
												alert(options.info_vote_success);
											}
										}
									}else{
										alert(options.info_vote_error);
									}
								});
							}else{
								$(".fn_login").trigger('click');
							}
						});
					}
					return false;
				});
				$(options.my_comment_dislike).live('click', function(e) {
					if(e.button == 0) {
						$t = $(this);
						$.getJSON(url_cek_login,{token:curToken}, function(data) {
							if(data.status == 1){
								var mcl_id = $t.attr('id');
								mcl_id = mcl_id.split('_');
								$.getJSON('http://api.kompas.com/widget/save_vote?jsoncallback=?',{cid:mcl_id[3],textid:mcl_id[4],type:0}, function(data) {
									if(data.status=1){
										var curtotal=$('#my_comment_dislike_skor_'+mcl_id[3]+'_'+mcl_id[4]).text();
										if($.cookie('list_id_disvote')==null){
											$.cookie('list_id_disvote',mcl_id[3]+'_'+mcl_id[4],{ expires: 1 });
											$('#my_comment_dislike_skor_'+mcl_id[3]+'_'+mcl_id[4]).text(parseInt(curtotal)+1);
											alert(options.info_disvote_success);
										}else{	
											var is_exist=0;
											var list_id_vote=$.cookie('list_id_disvote');
											data=list_id_vote.split('|');
											$.each(data,function(i,item){
												if(item==mcl_id[3]+'_'+mcl_id[4]){
													is_exist=1;
													return;
												}
											});
											if(is_exist==1){
												alert(options.info_disvote_already);
											}else{
												list_id_vote=list_id_vote+'|'+mcl_id[3]+'_'+mcl_id[4];
												$.cookie('list_id_disvote',list_id_vote,{ expires: 1 });
												$('#my_comment_dislike_skor_'+mcl_id[3]+'_'+mcl_id[4]).text(parseInt(curtotal)+1);
												alert(options.info_disvote_success);
											}
										}
									}else{
										alert(options.info_vote_error);
									}
								});
							}else{
								$(".fn_login").trigger('click');
							}
						});
					}
					return false;
				});
			}
		});
	});
})(jQuery);
function getComment(articleID,page){
	jQuery('#my_comment_list').html('<div align="center"><img src="http://assets.kompas.com/data/2k11/comment/images/ajax-loader.gif" align="middle" /></div>');
	//jQuery('#my_comment_paging').html('');
	jQuery.getJSON('http://api.kompas.com/widget/get_comments/'+articleID+'/'+page+'?jsoncallback=?',function(data){
		jQuery('#my_comment_total').html(data.results.total_comment);
		jQuery('#my_comment_list').html(data.results.comments);
		jQuery('#my_comment_paging').html(data.results.pagging);
		jQuery('#my_comment_paging a').bind('click',function(){
			next_page=jQuery(this).attr('id');
			getComment(articleID,next_page.replace('pc',''));
			jQuery.scrollTo('#topkomen',500);                                     	
			return false;
		});
	});
}
function showlayer(layer){
	jQuery('#'+layer).css('display', 'none').slideDown('fast');
	return false;
}
function hidelayer(layer){
	jQuery('#'+layer).css('display', 'none');
	return false;
}