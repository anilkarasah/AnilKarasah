MYSS SEGMENT PARA STACK 'STS'
		DW		64 DUP (?)
MYSS ENDS

MYDS SEGMENT PARA 'DTS'
	cr			EQU		13
	lf			EQU		10
	hata		DB 		cr, lf, 'Warning !!! You did not enter a number, please re-enter !!!  ', 0
	menu		DB		cr, lf, 'Choose operation', lf, '1) Enter a list', lf,'2) View the list', lf, '3) Add new element', lf, '0) EXIT', lf, '> ', 0
	menugcrsiz	DB		cr, 'Warning !!! Please choose a proper operation !!!', lf, 0
	elemansayi	DB		'th element: ', 0
	n			DW		?
	menu2sutun	DB		lf, cr, lf, 'INDEX | ARRAY | ADDRESS', lf, cr, 0
	menu2ayrac	DB		'   |   ', 0
	menuwarn1	DB		lf, '!!!! You cannot anter a new list if you already have !!!!', lf, 0
	menuwarn2	DB		lf, '!!!! Please enter a list before this operation !!!!', lf, 0
	menu2head	DB		lf, 'Index of smallest element: ', 0
	menu1		DB		cr, lf, 'Enter the size of array: ', 0
	menu2		DB		cr, lf, 'Current array:', lf, 0
	menu2tam	DB		cr, lf, 'Array shown in order:', lf, 0
	menu3		DB		cr, lf, 'Enter new element: ', 0
	menucik		DB		cr, lf, 'PROGRAM TERMINATED', 0
	dizi		DW		100 DUP(?)
	adres		DW		-2, 99 DUP(?)
	head		DW		0
	menu1flag	DB		0
MYDS ENDS

MYCS SEGMENT PARA 'CDS'
	ASSUME CS:MYCS, DS:MYDS, SS:MYSS
	
MAIN	PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, MYDS
		MOV DS, AX
		
MENUBAS:
		CALL PRINT_MENU			; AX ile menüde seçilen değer döndürüldü
		
		CMP BX, 0
		JE MENUSECCIKIS
		CMP BX, 1
		JE MENUSEC1
		CMP BX, 2
		JE MENUSEC2
		CMP BX, 3
		JE MENUSEC3
		JMP MENUSECGCRSIZ
MENUSEC1:
		CALL MENUYAZ1
		JMP MENUBAS
MENUSEC2:
		CALL MENUYAZ2
		JMP MENUBAS
MENUSEC3:
		CALL MENUYAZ3
		JMP MENUBAS
MENUSECGCRSIZ:
		LEA AX, menugcrsiz
		CALL PUT_STR
		JMP MENUBAS
MENUSECCIKIS:
		LEA AX, menucik
		CALL PUT_STR
	
	RETF
MAIN ENDP

PRINT_MENU	PROC NEAR
		PUSH AX
		;	BX ile menü için girilen değer (SEÇİM) döner
		LEA AX, menu
		CALL PUT_STR
		
		;	string olarak sayı inputu alır
		CALL GETN
		MOV BX, AX
		POP AX
	RET
PRINT_MENU	ENDP

MENUYAZ1	PROC NEAR
		PUSH AX
		PUSH CX
		PUSH SI
		
		CMP menu1flag, 0
		JNE MENU1UYARI
		
		MOV menu1flag, 1	;	dizinin girildiğini set eder
		;	dizi kaç elemanlı?
		LEA AX, menu1
		CALL PUT_STR
		CALL GETN
		MOV n, AX
		MOV CX, AX
		XOR SI, SI
		;	dizi elemanlarının alınması
ELEMANAL:
		;	kaçıncı elemanın girileceğini yazdırır
		MOV AX, SI
		SHR AX, 1
		INC AX
		CALL PUTN
		LEA AX, elemansayi
		CALL PUT_STR
		;	OUTPUT:		i. elemani giriniz
		;	ilgili indise kullanıcıdan sayı alma kısmı
		CALL GETN
		MOV dizi[SI], AX
		CALL LINKEKLE
		ADD SI, 2
		LOOP ELEMANAL
		JMP MENU1CIKIS
MENU1UYARI:
		LEA AX, menuwarn1
		CALL PUT_STR
MENU1CIKIS:
		POP SI
		POP CX
		POP AX
	RET
MENUYAZ1	ENDP

LINKEKLE	PROC NEAR
		;	AX ile gelen değeri linkli listeye ekler
		;	SI ile şuanki indisin değeri gelir
		PUSH DI
		PUSH BX
		
		;	daha önce hiç eleman eklenmiş mi?
		CMP adres[0], -2	;	diziye daha önce eleman eklenmediyse, adres dizisinin ilk indisi -2
		JNE ILKELEMANDEGIL
		MOV adres[0], -1	;	ilk eleman eklenince adres dizisinin ilk indisi -1 oluyor
		MOV dizi[0], AX
		JMP LINKCIKIS
ILKELEMANDEGIL:
		;	yeni eklenecek elemanın head'in öncesine yerleştirilmesi gerekiyor mu?
		MOV DI, head
		SHL DI, 1
		CMP AX, dizi[DI]
		JG LINKWHILE
		SHR DI, 1
		MOV adres[SI], DI
		SHL DI, 1
		SHR SI, 1
		MOV head, SI
		SHL SI, 1
		JMP LINKCIKIS
LINKWHILE:
		CMP adres[DI], -1
		JE LINKWHILESON
		MOV BX, adres[DI]	;	DI'da hala adres[SI] saklanıyor
		SHL BX, 1
		CMP AX, dizi[BX]
		JL LINKWHILESON
		MOV DI, BX
		JMP LINKWHILE
LINKWHILESON:
		MOV BX, adres[DI]
		MOV adres[SI], BX
		SHR SI, 1
		MOV adres[DI], SI
		SHL SI, 1

LINKCIKIS:
		POP BX
		POP DI
	RET
LINKEKLE	ENDP

MENUYAZ2	PROC NEAR
		PUSH AX
		PUSH CX
		PUSH SI
		
		;	eğer herhangi bir dizi girilmediyse uyarı verir
		CMP menu1flag, 0	;	0'da dizi henüz girilmemiş
		JE MENU2UYARI
		
		LEA AX, menu2sutun
		CALL PUT_STR
		MOV CX, n
		XOR SI, SI
MENU2YAZDIR:
		;	indis sütununa yazdır
		MOV AX, SI
		SHR AX, 1
		CALL PUTN
		; araya '|' karakterini bastır
		LEA AX, menu2ayrac
		CALL PUT_STR
		;	dizi arrayinin ilgili indisindeki değeri yazdırır
		MOV AX, dizi[SI]
		CALL PUTN
		; araya '|' karakterini bastır
		LEA AX, menu2ayrac
		CALL PUT_STR
		;	adres arrayinin ilgili indisindeki değeri yazdırır
		MOV AX, adres[SI]
		CALL PUTN
		;	alt satıra geç
		MOV AL, lf	; lf: alt satır karakteri
		CALL PUTC
		
		ADD SI, 2
		LOOP MENU2YAZDIR
		
		;	head'i yazdırma kısmı
		LEA AX, menu2head
		CALL PUT_STR
		MOV AX, head
		CALL PUTN
		MOV AL, lf
		CALL PUTC
		
		;	listenin sıralı yazdırıldığı kısım
		LEA AX, menu2tam
		CALL PUT_STR
		MOV SI, head
MENU2LISTEYAZ:
		SHL SI, 1
		MOV AX, dizi[SI]
		CALL PUTN
		MOV CX, adres[SI]
		CMP CX, -1
		JE MENU2LISTEYAZILDI
		MOV AL, 32	; 32: boşluk karakteri
		CALL PUTC
		MOV SI, CX
		JMP MENU2LISTEYAZ
MENU2LISTEYAZILDI:
		MOV AL, lf
		CALL PUTC
		JMP MENU2CIKIS
		
MENU2UYARI:
		LEA AX, menuwarn2
		CALL PUT_STR
MENU2CIKIS:
		POP SI
		POP CX
		POP AX
	RET
MENUYAZ2	ENDP

MENUYAZ3	PROC NEAR
		PUSH AX
		PUSH BX
		
		;	eğer herhangi bir dizi girilmediyse uyarı verir
		CMP menu1flag, 0	;	0'da dizi henüz girilmemiş
		JE MENU3UYARI
		
		LEA AX, menu3
		CALL PUT_STR
		CALL GETN
		MOV SI, n
		SHL SI, 1
		MOV dizi[SI], AX
		CALL LINKEKLE
		INC n
		JMP MENU3CIKIS
MENU3UYARI:
		LEA AX, menuwarn2
		CALL PUT_STR
MENU3CIKIS:
		POP BX
		POP AX
	RET
MENUYAZ3	ENDP

GETC	PROC NEAR
		;------------------------------------------------------------------------
		; Klavyeden basılan karakteri AL yazmacına alır ve ekranda gösterir. 
		; işlem sonucunda sadece AL etkilenir. 
		;------------------------------------------------------------------------
		MOV AH, 1h
		INT 21H
		RET 
GETC	ENDP 

PUTC	PROC NEAR
        ;------------------------------------------------------------------------
        ; AL yazmacındaki değeri ekranda gösterir. DL ve AH değişiyor. AX ve DX 
        ; yazmaçlarının değerleri korumak için PUSH/POP yapılır. 
        ;------------------------------------------------------------------------
        PUSH AX
        PUSH DX
        MOV DL, AL
        MOV AH,2
        INT 21H
        POP DX
        POP AX
        RET 
PUTC 	ENDP 

GETN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; Klavyeden basılan sayiyi okur, sonucu AX yazmacı üzerinden dondurur. 
        ; DX: sayının işaretli olup/olmadığını belirler. 1 (+), -1 (-) demek 
        ; BL: hane bilgisini tutar 
        ; CX: okunan sayının islenmesi sırasındaki ara değeri tutar. 
        ; AL: klavyeden okunan karakteri tutar (ASCII)
        ; AX zaten dönüş değeri olarak değişmek durumundadır. Ancak diğer 
        ; yazmaçların önceki değerleri korunmalıdır. 
        ;------------------------------------------------------------------------
        PUSH BX
        PUSH CX
        PUSH DX
GETN_START:
        MOV DX, 1	                        ; sayının şimdilik + olduğunu varsayalım 
        XOR BX, BX 	                        ; okuma yapmadı Hane 0 olur. 
        XOR CX,CX	                        ; ara toplam değeri de 0’dır. 
NEW:
        CALL GETC	                        ; klavyeden ilk değeri AL’ye oku. 
        CMP AL,CR 
        JE FIN_READ	                        ; Enter tuşuna basilmiş ise okuma biter
        CMP  AL, '-'	                        ; AL ,'-' mi geldi ? 
        JNE  CTRL_NUM	                        ; gelen 0-9 arasında bir sayı mı?
NEGATIVE:
        MOV DX, -1	                        ; - basıldı ise sayı negatif, DX=-1 olur
        JMP NEW		                        ; yeni haneyi al
CTRL_NUM:
        CMP AL, '0'	                        ; sayının 0-9 arasında olduğunu kontrol et.
        JB error 
        CMP AL, '9'
        JA error		                ; değil ise HATA mesajı verilecek
        SUB AL,'0'	                        ; rakam alındı, haneyi toplama dâhil et 
        MOV BL, AL	                        ; BL’ye okunan haneyi koy 
        MOV AX, 10 	                        ; Haneyi eklerken *10 yapılacak 
        PUSH DX		                        ; MUL komutu DX’i bozar işaret için saklanmalı
        MUL CX		                        ; DX:AX = AX * CX
        POP DX		                        ; işareti geri al 
        MOV CX, AX	                        ; CX deki ara değer *10 yapıldı 
        ADD CX, BX 	                        ; okunan haneyi ara değere ekle 
        JMP NEW 		                ; klavyeden yeni basılan değeri al 
ERROR:
        MOV AX, OFFSET HATA 
        CALL PUT_STR	                        ; HATA mesajını göster 
        JMP GETN_START                          ; o ana kadar okunanları unut yeniden sayı almaya başla 
FIN_READ:
        MOV AX, CX	                        ; sonuç AX üzerinden dönecek 
        CMP DX, 1	                        ; İşarete göre sayıyı ayarlamak lazım 
        JE FIN_GETN
        NEG AX		                        ; AX = -AX
FIN_GETN:
        POP DX
        POP CX
        POP DX
        RET 
GETN 	ENDP 

PUTN 	PROC NEAR
        ;------------------------------------------------------------------------
        ; AX de bulunan sayiyi onluk tabanda hane hane yazdırır. 
        ; CX: haneleri 10’a bölerek bulacağız, CX=10 olacak
        ; DX: 32 bölmede işleme dâhil olacak. Soncu etkilemesin diye 0 olmalı 
        ;------------------------------------------------------------------------
        PUSH CX
        PUSH DX 	
        XOR DX,	DX 	                        ; DX 32 bit bölmede soncu etkilemesin diye 0 olmalı 
        PUSH DX		                        ; haneleri ASCII karakter olarak yığında saklayacağız.
                                                ; Kaç haneyi alacağımızı bilmediğimiz için yığına 0 
                                                ; değeri koyup onu alana kadar devam edelim.
        MOV CX, 10	                        ; CX = 10
        CMP AX, 0
        JGE CALC_DIGITS	
        NEG AX 		                        ; sayı negatif ise AX pozitif yapılır. 
        PUSH AX		                        ; AX sakla 
        MOV AL, '-'	                        ; işareti ekrana yazdır. 
        CALL PUTC
        POP AX		                        ; AX’i geri al 
        
CALC_DIGITS:
        DIV CX  		                ; DX:AX = AX/CX  AX = bölüm DX = kalan 
        ADD DX, '0'	                        ; kalan değerini ASCII olarak bul 
        PUSH DX		                        ; yığına sakla 
        XOR DX,DX	                        ; DX = 0
        CMP AX, 0	                        ; bölen 0 kaldı ise sayının işlenmesi bitti demek
        JNE CALC_DIGITS	                        ; işlemi tekrarla 
        
DISP_LOOP:
                                                ; yazılacak tüm haneler yığında. En anlamlı hane üstte 
                                                ; en az anlamlı hane en alta ve onu altında da 
                                                ; sona vardığımızı anlamak için konan 0 değeri var. 
        POP AX		                        ; sırayla değerleri yığından alalım
        CMP AX, 0 	                        ; AX=0 olursa sona geldik demek 
        JE END_DISP_LOOP 
        CALL PUTC 	                        ; AL deki ASCII değeri yaz
        JMP DISP_LOOP                           ; işleme devam
        
END_DISP_LOOP:
        POP DX 
        POP CX
        RET
PUTN 	ENDP 

PUT_STR	PROC NEAR
        ;------------------------------------------------------------------------
        ; AX de adresi verilen sonunda 0 olan dizgeyi karakter karakter yazdırır.
        ; BX dizgeye indis olarak kullanılır. Önceki değeri saklanmalıdır. 
        ;------------------------------------------------------------------------
	PUSH BX 
        MOV BX,	AX			        ; Adresi BX’e al 
        MOV AL, BYTE PTR [BX]	                ; AL’de ilk karakter var 
PUT_LOOP:   
        CMP AL,0		
        JE  PUT_FIN 			        ; 0 geldi ise dizge sona erdi demek
        CALL PUTC 			        ; AL’deki karakteri ekrana yazar
        INC BX 				        ; bir sonraki karaktere geç
        MOV AL, BYTE PTR [BX]
        JMP PUT_LOOP			        ; yazdırmaya devam 
PUT_FIN:
	POP BX
	RET 
PUT_STR	ENDP
	
mycs ends
end main