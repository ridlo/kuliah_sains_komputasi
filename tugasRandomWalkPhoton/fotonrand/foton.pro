pro foton

Folder='C:\Users\ridlo\Documents\fotonrand\'
file1='Randomwalk-Constant005.txt'
file2='Randomwalk-Constant05.txt'
file3='Randomwalk-Constant5.txt'

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

n1 = data1.FIELD1
t1 = data1.FIELD2
n2 = data2.FIELD1
t2 = data2.FIELD2
n3 = data3.FIELD1
t3 = data3.FIELD2

nb1=100
ht1=histogram(t1,nbins=nb1)
nel1=n_elements(ht1)
bz1 = (max(t1) - min(t1))/ 100
bin1=bz1*findgen(nel1)+min(t1)
openw,nulis,Folder+'005.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[bin1[ff],ht1[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 100)
close,nulis
free_lun,nulis

nb2=100
ht2=histogram(t2,nbins=nb2)
nel2=n_elements(ht2)
bz2 = (max(t2) - min(t2))/ 100
bin2=bz2*findgen(nel2)+min(t2)
openw,nulis,Folder+'05.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[bin2[ff],ht2[ff],0.1],format='(F7.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 100)
close,nulis
free_lun,nulis

nb3=100
ht3=histogram(t3,nbins=nb3)
nel3=n_elements(ht3)
bz3 = (max(t3) - min(t3))/ 100
bin3=bz3*findgen(nel3)+min(t3)
openw,nulis,Folder+'5.txt',/get_lun
ff=0.
repeat begin
	printf,nulis,[bin3[ff],ht3[ff],0.1],format='(F14.3,1X,F7.3,1X,F7.3)'
	ff=ff+1.
endrep until (ff eq 100)
close,nulis
free_lun,nulis

window,0
plot,alog10(bin3),ht3,psym=10, background='ffffff'x, color='000000'x, xrange=[0.,4.], yrange=[0.,60.],$
	xtitle="log(tm)", ytitle="# of occurances", title="distribution for different R_rad in 1000 running"
;window,1
oplot,alog10(bin2),ht2,psym=10,color='ff0000'x
;window,2
oplot,alog10(bin1),ht1,psym=10,color='0000ff'x

;window,1
;plot,bin3,ht3,psym=10, background='ffffff'x, color='000000'x,$
;	xtitle="log(tm)", ytitle="# of occurances", title="distribution for different R_rad in 1000 running"

end