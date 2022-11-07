; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; 僆僽僕僃僋僩僼傽僀儖傪嶌傞儌乕僪
[INSTRSET "i486p"]
[BITS 32]						; 32價僢僩儌乕僪梡偺婡夿岅傪嶌傜偣傞


; 僆僽僕僃僋僩僼傽僀儖偺偨傔偺忣曬

[FILE "naskfunc.nas"]			; 僜乕僗僼傽僀儖柤忣曬

		GLOBAL	_io_hlt,_write	,_test,_oi_cli,_oi_sti,_oi_8in,_oi_8out,_oi_16in,_oi_16out,_oi_32in,_oi_32out,_oi_load_eflags,_oi_store_eflags		; 偙偺僾儘僌儔儉偵娷傑傟傞娭悢柤
		
; 埲壓偼幚嵺偺娭悢

[SECTION .text]		; 僆僽僕僃僋僩僼傽僀儖偱偼偙傟傪彂偄偰偐傜僾儘僌儔儉傪彂偔
_oi_sti:
		sti
		ret
_oi_cli:
		cli
		ret
_oi_8in:
		mov edx,[esp+4]
		mov eax,0	
		in	al,dx
		ret
_oi_16in:
		mov edx,[esp+4]
		mov eax,0
		in   eax,dx
		ret
_oi_32in:
		mov edx,[esp+4]
		
		in eax,dx
		ret
_oi_8out:
		mov edx,[esp+4]
		mov al,[esp+8]
		out dx,al
		ret
_oi_16out:
		mov edx,[esp+4]
		mov ax,[esp+8]
		out dx,ax
		ret
_oi_32out:
		mov edx,[esp+4]
		mov eax,[esp+8]
		out dx,eax
		ret
		
_test:
		DB "HEIGE"
		ret
