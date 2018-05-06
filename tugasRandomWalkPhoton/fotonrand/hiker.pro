pro hiker

Folder='C:\Users\ridlo\Documents\fotonrand\'
file1='hikerstat-10.txt'
file2='hikerstat-20.txt'
file3='hikerstat-50.txt'
file4='hikerstat-100.txt'

;template
caritemplatesdss=file_search(Folder+'template_2.sav')
if (caritemplatesdss NE "") then begin
    restore, Folder+'template_2.sav', restored_object=templatesdss
endif else begin
    templatesdss= ascii_template(Folder+file, cancel=bataltemplatesdss)
    if (bataltemplatesdss NE 1) then begin
       save, templatesdss, FileName = Folder+'template_2.sav'
    endif else begin
    print,"gak ada template dul, STOP!"
    stop
    endelse
endelse

data1=read_ascii(Folder+file1, template = templatesdss)
data2=read_ascii(Folder+file2, template = templatesdss)
data3=read_ascii(Folder+file3, template = templatesdss)
data4=read_ascii(Folder+file4, template = templatesdss)

n1 = data1.FIELD1
t1 = data1.FIELD2
n2 = data2.FIELD1
t2 = data2.FIELD2
n3 = data3.FIELD1
t3 = data3.FIELD2
n4 = data4.FIELD1
t4 = data4.FIELD2

;nb1=100
;ht1=histogram(t1,nbins=nb1)
;nel1=n_elements(ht1)
;bz1 = (max(t1) - min(t1))/ 100
;bin1=bz1*findgen(nel1)+min(t1)
;openw,nulis,Folder+'10.txt',/get_lun
;ff=0.
;repeat begin
;	printf,nulis,[bin1[ff],ht1[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
;	ff=ff+1.
;endrep until (ff eq 100)
;close,nulis
;free_lun,nulis
;
;nb2=100
;ht2=histogram(t2,nbins=nb2)
;nel2=n_elements(ht2)
;bz2 = (max(t2) - min(t2))/ 100
;bin2=bz2*findgen(nel2)+min(t2)
;openw,nulis,Folder+'20.txt',/get_lun
;ff=0.
;repeat begin
;	printf,nulis,[bin2[ff],ht2[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
;	ff=ff+1.
;endrep until (ff eq 100)
;close,nulis
;free_lun,nulis
;
;nb3=100
;ht3=histogram(t3,nbins=nb3)
;nel3=n_elements(ht3)
;bz3 = (max(t3) - min(t3))/ 100
;bin3=bz3*findgen(nel3)+min(t3)
;openw,nulis,Folder+'50.txt',/get_lun
;ff=0.
;repeat begin
;	printf,nulis,[bin3[ff],ht3[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
;	ff=ff+1.
;endrep until (ff eq 100)
;close,nulis
;free_lun,nulis
;
;nb4=100
;ht4=histogram(t4,nbins=nb4)
;nel4=n_elements(ht4)
;bz4 = (max(t4) - min(t4))/ 100
;bin4=bz4*findgen(nel4)+min(t4)
;openw,nulis,Folder+'100.txt',/get_lun
;ff=0.
;repeat begin
;	printf,nulis,[bin4[ff],ht4[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
;	ff=ff+1.
;endrep until (ff eq 100)
;close,nulis
;free_lun,nulis
;
;window,0
;plot,bin4,ht4,psym=10, background='ffffff'x, color='000000'x,xrange=[-!PI,!PI],yrange=[0,120],$
;	xtitle="theta (rad)", ytitle="# of occurances", title="angle dist of final position relatif to center, for different R_max in 1000 running"
;oplot,bin3,ht3,psym=10,color='ff0000'x
;oplot,bin2,ht2,psym=10,color='00ff00'x
;oplot,bin1,ht1,psym=10,color='0000ff'x

nb1=20
hn1=histogram(n1,nbins=nb1)
neln1=n_elements(hn1)
bzn1 = (max(n1) - min(n1))/20
binn1=bzn1*findgen(neln1)+min(n1)
openw,nulis,Folder+'10n.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[binn1[ff],hn1[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 20)
close,nulis
free_lun,nulis

nb2=20
hn2=histogram(n2,nbins=nb2)
neln2=n_elements(hn2)
bzn2 = (max(n2) - min(n2))/20
binn2=bzn2*findgen(neln2)+min(n2)
openw,nulis,Folder+'20n.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[binn2[ff],hn2[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 20)
close,nulis
free_lun,nulis

nb3=20
hn3=histogram(n3,nbins=nb3)
neln3=n_elements(hn3)
bzn3 = (max(n3) - min(n3))/20
binn3=bzn3*findgen(neln3)+min(n3)
openw,nulis,Folder+'50n.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[binn3[ff],hn3[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 20)
close,nulis
free_lun,nulis

nb4=20
hn4=histogram(n4,nbins=nb4)
neln4=n_elements(hn4)
bzn4 = (max(n4) - min(n4))/20
binn4=bzn4*findgen(neln4)+min(n4)
openw,nulis,Folder+'100n.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[binn4[ff],hn4[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 20)
close,nulis
free_lun,nulis

window,1
plot,alog10(binn4),hn4,psym=10, background='ffffff'x, color='000000'x,xrange=[1,2.5],$
	xtitle="log10(# step)", ytitle="# of occurances", title="# of steps distribution in 1000 running, R_max=100"
oplot,alog10(binn3),hn3,psym=10,color='ff0000'x
oplot,alog10(binn2),hn2,psym=10,color='00ff00'x
oplot,alog10(binn1),hn1,psym=10,color='0000ff'x

;window,2
;plot,binn3,hn3,psym=10, background='ffffff'x, color='000000'x,$
;	xtitle="# step", ytitle="# of occurances", title="# of steps distribution in 1000 running, R_max=50"
;
;window,3
;plot,binn2,hn2,psym=10, background='ffffff'x, color='000000'x,$
;	xtitle="# step", ytitle="# of occurances", title="# of steps distribution in 1000 running, R_max=20"
;
;window,4
;plot,binn1,hn1,psym=10, background='ffffff'x, color='000000'x,$
;	xtitle="# step", ytitle="# of occurances", title="# of steps distribution in 1000 running, R_max=10"

end