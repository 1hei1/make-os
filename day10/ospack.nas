; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; 僆僽僕僃僋僩僼傽僀儖傪嶌傞儌乕僪
[INSTRSET "i486p"]
[BITS 32]						; 32價僢僩儌乕僪梡偺婡夿岅傪嶌傜偣傞


; 僆僽僕僃僋僩僼傽僀儖偺偨傔偺忣曬

[FILE "naskfunc.nas"]			; 僜乕僗僼傽僀儖柤忣曬

		GLOBAL	_io_hlt,_write	,_test,_oi_cli,_oi_sti,_oi_8in,_oi_8out,_oi_16in,_oi_16out,_oi_32in,_oi_32out,_oi_load_eflags,_oi_store_eflags,_gdt_save,_idt_save	,_asm_inthandler,_asm_inthandler27,_asm_inthandler2c,_memory_size,_load_cr0,_store_cr0; 偙偺僾儘僌儔儉偵娷傑傟傞娭悢柤
EXTERN _JIANPAN,_shubiao,_shubiaodate
		
; 埲壓偼幚嵺偺娭悢

[SECTION .text]		; 僆僽僕僃僋僩僼傽僀儖偱偼偙傟傪彂偄偰偐傜僾儘僌儔儉傪彂偔

_oi_sti:
		sti
		ret              ;启用中断
_oi_cli:
		cli
		ret              ;禁用中断
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

_write:
  		MOV ECX,[ESP+4]       ;写入到指定地址（地址，数据）
		MOV AL,[ESP+8]
		MOV [ECX],AL
		
		RET
_oi_load_eflags:
		pushfd
		pop eax
		ret
_oi_store_eflags:
		mov eax,[esp+4]
		push eax
		popfd
		ret
_load_cr0:
		mov eax,cr0
		ret
_store_cr0:
		mov eax,[esp+4]
		mov cro,eax
		ret
_io_hlt:	; void io_hlt(void);
		HLT
		RET
_gdt_save:
		MOV AX,[ESP+4]
		MOV [ESP+6],AX
		LGDT [ESP+6]
		RET
_idt_save:
		MOV AX,[ESP+4]
		MOV [ESP+6],AX
		LIDT [ESP+6]
		RET
_asm_inthandler:                ;键盘中断程序
PUSH ES
PUSH DS
PUSHAD
MOV EAX,ESP
PUSH EAX
MOV AX,SS
MOV DS,SS
MOV ES,AX
CALL _JIANPAN
POP EAX
POPAD
POP DS
POP ES
IRETD


_asm_inthandler27:           ;27号中断处理程序
PUSH ES
PUSH DS
PUSHAD
MOV EAX,ESP
PUSH EAX
MOV AX,SS
MOV DS,SS
MOV ES,AX
CALL _shubiao
POP EAX
POPAD
POP DS
POP ES
IRETD

_asm_inthandler2c:              ;2c号中断处理程序
PUSH ES
PUSH DS
PUSHAD
MOV EAX,ESP
PUSH EAX
MOV AX,SS
MOV DS,SS
MOV ES,AX
CALL _shubiaodate
POP EAX
POPAD
POP DS
POP ES
IRETD


_memory_size:              ;这是检测计算机内存的程序
	PUSH EDI
	PUSH ESI
	PUSH EBX
	MOV EDI,0Xaa55aa55
	MOV ESI,0x55aa55aa
	MOV EAX,[ESP+12+4]	
LOOPSTART:
	MOV EBX,EAX
	ADD EBX,0XFFC
	MOV EDX,[EBX]
	MOV [EBX],EDI
	XOR DWORD [EBX],0XFFFFFFFF
	CMP ESI,[EBX]
	JNZ MAX
	XOR DWORD [EBX],0XFFFFFFFF
	CMP EDI,[EBX]
	JNZ MAX
	MOV [EBX],EDX
	ADD EAX,0X1000
	CMP EAX,[ESP+12+8]
	JBE LOOPSTART
	POP EBX
	POP ESI
	POP EDI
	RET
MAX:
	MOV [EBX],EDX
	POP EBX
	POP ESI
	POP EDI
	RET

	
	
