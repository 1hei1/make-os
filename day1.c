ORG 0X7C00 


MOV AX,0
MOV DS,AX
MOV ES,AX
MOV SS,AX
MOV SP,0X7c00
MOV SI,msg     ；寄存器初始化

circle:        ；进入循环一次一个字符
MOV AL,[SI]    ；默认ds：si  al中存放输出字符
ADD SI,1
CMP AL,0       
JE fin
MOV AH,0X0e    ；功能号0e
MOV BX,15      ；颜色
INT 0X10       ；16号中断
JMP circle

msg:
DB   "HELLO,OS"
DB   "I name it :"
DB   "@Black Dragn@"
DB    0

fin:   :注意冒号不能是中文冒号
HLT
JMP fin
RESB 0x7dfe-$
DB 0x55,0xaa
