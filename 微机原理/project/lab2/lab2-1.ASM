DSEG SEGMENT
	ARY 	DB 06H,0F2H,5AH,0F4H,97H,64H,0BBH,7FH,0FH,0D8H	;数据值
	N 	DW 10								;数据量为10
	MAX 	DB ?								;用于存放最大值
	KEY	DB 'MAX=',0DH,0AH,'$'
DSEG ENDS									;数据段结束

CSEG SEGMENT
	ASSUME CS:CSEG,DS:DSEG
START:
	MOV 	AX,DSEG
	MOV 	DS,AX
	MOV 	CX,N				;内循环次数送给CX，初始值为N-1
	DEC 	CX				;CX自减
	MOV 	SI,4000H			;偏移地址送给SI
L1:	MOV 	DI,CX				;内循环次数存在DI中，初始值为CX-1
	MOV 	BX,0
L2:	MOV 	AL,ARY[BX]			;地址指针预设值为0
	CMP 	AL,ARY[BX+1]		;相邻两数据比较，由于数位8位，因此地址值+1即可
	JAE 	COTINUE			;若两数比较符合排序，则跳转到CONTINUE
	XCHG 	AL,ARY[BX+1]		;否则，将两数交换
	MOV 	ARY[BX],AL			;ARY当前位置存较大的数
COTINUE:
	ADD 	BX,1				;修改地址指针
	LOOP 	L2
	;内循环结束
	MOV 	AL,ARY[BX]			;暂时保存
	MOV 	[SI],AL			;在偏移地址SI处储存当前的最小值
	INC 	SI				;字节操作，SI+1

	MOV 	CX,DI
	LOOP	L1
	;外循环结束

	LEA	DX,KEY			;字符串起始地址送给DX
	MOV	AH,09H			;字符串显示功能
	INT	21H				;显示字符串'MAX='

	MOV 	AL,ARY[0]			;将最大值送给AL
	SHR 	AL,4 				;取出高4位
	CALL	one_hex_to_ascii 		;将高4位转换为ASCII码
	MOV	AH,02H			;功能号02H，显示字符
	MOV	DL,AL				;要显示的字符的ASCII码存入DL
	INT	21H				;DOS调用

	MOV 	AL,ARY[0] 			;取出16进制数
	AND 	AL,0FH 			;取出低4位
	CALL	one_hex_to_ascii		;将低4位转换为ASCII码
	MOV	AH,02H			;功能号02H，显示字符
	MOV	DL,AL				;要显示的字符的ASCII码存入DL
	INT	21H				;DOS调用

	MOV	AH,4CH			;功能号送AH
	INT	21H				;返回DOS

;输入: AL为1位16进制数
;输出: AL为对应的ASCII码
one_hex_to_ascii:
	CMP	AL,0AH 			;判断是否小于10
    	JL	one_hex_digit ;如果小于10，跳转到处理一位数字的情况
    	ADD	AL,07H			;将大于10的16进制数转换为对应的大写字母
one_hex_digit:
    	ADD 	AL,'0' 	;将数字转换为对应的ASCII码
    	RET

CSEG ENDS
	END START

