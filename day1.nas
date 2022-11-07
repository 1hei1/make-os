; haribote-ipl
; TAB=4

CYLS	EQU		10				; 偳偙傑偱撉傒崬傓偐

		ORG		0x7c00			; 偙偺僾儘僌儔儉偑偳偙偵撉傒崬傑傟傞偺偐
		JMP		entry
; 埲壓偼昗弨揑側FAT12僼僅乕儅僢僩僼儘僢僺乕僨傿僗僋偺偨傔偺婰弎

	
		DB		0x90
		DB		"HARIBOTE"		; 僽乕僩僙僋僞偺柤慜傪帺桼偵彂偄偰傛偄乮8僶僀僩乯
		DW		512				; 1僙僋僞偺戝偒偝乮512偵偟側偗傟偽偄偗側偄乯
		DB		1				; 僋儔僗僞偺戝偒偝乮1僙僋僞偵偟側偗傟偽偄偗側偄乯
		DW		1				; FAT偑偳偙偐傜巒傑傞偐乮晛捠偼1僙僋僞栚偐傜偵偡傞乯
		DB		2				; FAT偺屄悢乮2偵偟側偗傟偽偄偗側偄乯
		DW		224				; 儖乕僩僨傿儗僋僩儕椞堟偺戝偒偝乮晛捠偼224僄儞僩儕偵偡傞乯
		DW		2880			; 偙偺僪儔僀僽偺戝偒偝乮2880僙僋僞偵偟側偗傟偽偄偗側偄乯
		DB		0xf0			; 儊僨傿傾偺僞僀僾乮0xf0偵偟側偗傟偽偄偗側偄乯
		DW		9				; FAT椞堟偺挿偝乮9僙僋僞偵偟側偗傟偽偄偗側偄乯
		DW		18				; 1僩儔僢僋偵偄偔偮偺僙僋僞偑偁傞偐乮18偵偟側偗傟偽偄偗側偄乯
		DW		2				; 僿僢僪偺悢乮2偵偟側偗傟偽偄偗側偄乯
		DD		0				; 僷乕僥傿僔儑儞傪巊偭偰側偄偺偱偙偙偼昁偢0
		DD		2880			; 偙偺僪儔僀僽戝偒偝傪傕偆堦搙彂偔
		DB		0,0,0x29		; 傛偔傢偐傜側偄偗偳偙偺抣偵偟偰偍偔偲偄偄傜偟偄
		DD		0xffffffff		; 偨傇傫儃儕儏乕儉僔儕傾儖斣崋
		DB		"HARIBOTEOS "	; 僨傿僗僋偺柤慜乮11僶僀僩乯
		DB		"FAT12   "		; 僼僅乕儅僢僩偺柤慜乮8僶僀僩乯
		RESB	18				; 偲傝偁偊偢18僶僀僩偁偗偰偍偔

; 僾儘僌儔儉杮懱
entry:
		MOV AX,0
		MOV SS,AX
		MOV SP,0X7C00
		MOV DS,AX

		MOV AX,0X0820
		MOV ES,AX
		MOV CH,0
		MOV DH,0
		
		MOV CL,2
		MOV AL,1
		
readloop:
		MOV SI,0
		
retry:
		MOV AH,0X02
		
		MOV AL,1
		MOV BX,0
		MOV DL,0x00
		INT 0X13
		JNC next
		ADD SI,1
		CMP SI,5
		JAE error
		MOV AH,0X00
		MOV DL,0X00
		INT 0X13
		JMP retry
next:
	     MOV		AX,ES			; 傾僪儗僗傪0x200恑傔傞
		ADD		AX,0x0020
		MOV		ES,AX		
		ADD		CL,1			; CL偵1傪懌偡
		CMP		CL,18			; CL偲18傪斾妑
		JBE		readloop		; CL <= 18 偩偭偨傜readloop傊
		MOV		CL,1
		ADD		DH,1
		CMP		DH,2
		JB		readloop		; DH < 2 偩偭偨傜readloop傊
		MOV		DH,0
		ADD		CH,1
		CMP		CH,CYLS
		JB		readloop
		MOV		[0X0FF0],CH
		JMP       0XC200
error:
		MOV SI,msg
		
loop:
		MOV AL,[SI]
		CMP AL,0
		JE fin
		
		MOV AH,0X0e
		MOV BX,15
		INT 0X10
		ADD SI,1
		JMP loop


error1:
		MOV SI,msg1
		
loop1:
		MOV AL,[SI]
		CMP AL,0
		JE fin
		
		MOV AH,0X0e
		MOV BX,15
		INT 0X10
		ADD SI,1
		JMP loop1

fin:
HLT
JMP fin

msg:
	DB "YOU ERROR"
	DB 0

msg1:
	DB "AL=1"
	DB 0		
		

		RESB	0x7dfe-$		; 0x7dfe傑偱傪0x00偱杽傔傞柦椷

		DB		0x55, 0xaa
