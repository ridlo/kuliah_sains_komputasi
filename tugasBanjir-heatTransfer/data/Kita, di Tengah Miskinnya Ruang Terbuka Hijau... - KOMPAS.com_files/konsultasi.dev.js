// JavaScript Document
jQuery(document).ready(function() {
	jQuery("#txtN").focus(function(){
		if(jQuery("#txtN").val()=="Nama"){
			jQuery("#txtN").val('');
		}
	});
	jQuery("#txtN").blur(function(){
		if(jQuery("#txtN").val()==""){
			jQuery("#txtN").val("Nama");
		}
	});
	jQuery("#txtU").focus(function(){
		if(jQuery("#txtU").val()=="Usia"){
			jQuery("#txtU").val('');
		}
	});
	jQuery("#txtU").blur(function(){
		if(jQuery("#txtU").val()==""){
			jQuery("#txtU").val("Usia");
		}
	});
	jQuery("#txtE").focus(function(){
		if(jQuery("#txtE").val()=="Email"){
			jQuery("#txtE").val('');
		}
	});
	jQuery("#txtE").blur(function(){
		if(jQuery("#txtE").val()==""){
			jQuery("#txtE").val("Email");
		}
	});
	jQuery("#txtK").focus(function(){
		if(jQuery("#txtK").val()=="Kota"){
			jQuery("#txtK").val('');
		}
	});
	jQuery("#txtK").blur(function(){
		if(jQuery("#txtK").val()==""){
			jQuery("#txtK").val("Kota");
		}
	});
	jQuery("#txtP").focus(function(){
		if(jQuery("#txtP").val()=="Pertanyaan"){
			jQuery("#txtP").val('');
		}
	});
	jQuery("#txtP").blur(function(){
		if(jQuery("#txtP").val()==""){
			jQuery("#txtP").val("Pertanyaan");
		}
	});
});
function validateEmail(email) {
   var reg = /^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/;
   if(reg.test(email) == false) {
      return false;
   }
   return true;
}
function valFrmKonsultasi(){
	thisform=document.frmKonsultasi;
	if(thisform.selK.options[thisform.selK.options.selectedIndex].value==''){
		alert('Silahkan pilih jenis konsultasi');
		thisform.selK.focus();
	}else if(thisform.txtN.value=="" || thisform.txtN.value=="Nama"){
		alert('Silahkan isi Nama Anda');
		thisform.txtN.focus();
	}else if(thisform.txtU.value=="" || thisform.txtU.value=="Usia"){
		alert('Silahkan isi Usia Anda');
		thisform.txtU.focus();
	}else if(thisform.txtE.value=="" || thisform.txtE.value=="Email"){
		alert('Silahkan isi Email Anda');
		thisform.txtE.focus();
	}else if(!validateEmail(thisform.txtE.value)){
		alert('Email Anda tidak valid');
		thisform.txtE.focus();
	}else if(thisform.txtK.value=="" || thisform.txtK.value=="Kota"){
		alert('Silahkan isi Kota Anda');
		thisform.txtK.focus();
	}else if(thisform.txtP.value=="" || thisform.txtP.value=="Pertanyaan"){
		alert('Silahkan isi Pertanyaan Anda');
		thisform.txtP.focus();
	}else if(thisform.recaptcha_response_field.value==""){
		alert('Silahkan isi security code');
		thisform.recaptcha_response_field.focus();
	}else{
		thisform.submit();
	}
}