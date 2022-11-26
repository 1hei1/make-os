; naskfunc
; TAB=4

[FORMAT "WCOFF"]				; �I�u�W�F�N�g�t�@�C������郂�[�h
[INSTRSET "i486p"]
[BITS 32]						; 32�r�b�g���[�h�p�̋@�B�����点��


; �I�u�W�F�N�g�t�@�C���̂��߂̏��

[FILE "naskfunc.nas"]			; �\�[�X�t�@�C�������

		GLOBAL	_io_hlt,_write	,_test,_oi_cli,_oi_sti,_oi_8in,_oi_8out,_oi_16in,_oi_16out,_oi_32in,_oi_32out,_oi_load_eflags,_oi_store_eflags,_gdt_save,_idt_save	,_asm_inthandler,_asm_inthandler27,_asm_inthandler2c,_memory_size,_load_cr0,_store_cr0; ���̃v���O�����Ɋ܂܂��֐���
EXTERN _JIANPAN,_shubiao,_shubiaodate
		
; �ȉ��͎��ۂ̊֐�

[SECTION .text]		; �I�u�W�F�N�g�t�@�C���ł͂���������Ă���v���O����������

_oi_sti:
		sti
		ret              ;�����ж�
_oi_cli:
		cli
		ret              ;�����ж�
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
  		MOV ECX,[ESP+4]       ;д�뵽ָ����ַ����ַ�����ݣ�
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
_asm_inthandler:                ;�����жϳ���
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


_asm_inthandler27:           ;27���жϴ������
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

_asm_inthandler2c:              ;2c���жϴ������
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


_memory_size:              ;���Ǽ�������ڴ�ĳ���
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

	
	
