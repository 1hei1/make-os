; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; オブジェクトファイルを作るモード
[INSTRSET "i486p"]
[BITS 32]						; 32ビットモード用の機械語を作らせる


; オブジェクトファイルのための情報

[FILE "naskfunc.nas"]			; ソースファイル名情報

		GLOBAL	_io_hlt,_write	,_test,_oi_cli,_oi_sti,_oi_8in,_oi_8out,_oi_16in,_oi_16out,_oi_32in,_oi_32out,_oi_load_eflags,_oi_store_eflags,_gdt_save,_idt_save	,_asm_inthandler,_asm_inthandler27,_asm_inthandler2c,_memory_size,_load_cr0,_store_cr0; このプログラムに含まれる関数名
EXTERN _JIANPAN,_shubiao,_shubiaodate
		
; 以下は実際の関数

[SECTION .text]		; オブジェクトファイルではこれを書いてからプログラムを書く

_oi_sti:
		sti
		ret              ;ﾆ?ﾓﾃﾖﾐｶﾏ
_oi_cli:
		cli
		ret              ;ｽ?ﾓﾃﾖﾐｶﾏ
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
  		MOV ECX,[ESP+4]       ;ﾐｴﾈ?ｵｽﾖｸｶｨｵﾘﾖｷ｣ｨｵﾘﾖｷ｣ｬﾊ?ｾﾝ｣ｩ
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
_asm_inthandler:                ;ｼ?ﾅﾌﾖﾐｶﾏｳﾌﾐ?
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


_asm_inthandler27:           ;27ｺﾅﾖﾐｶﾏｴｦﾀ?ｳﾌﾐ?
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

_asm_inthandler2c:              ;2cｺﾅﾖﾐｶﾏｴｦﾀ?ｳﾌﾐ?
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


_memory_size:              ;ﾕ簗ﾇｼ?ｲ箴ﾆﾋ羹?ﾄﾚｴ豬ﾄｳﾌﾐ?
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

	
	
