;--------------------------------------------------------------------------------
;通过入栈/出栈操作记录输入数据，实现两个数之间的加、减、乘、除运算，其中
;加法：两位加数、和范围均为：0~65536
;减法：被减数、减数、差范围均为：-32767~32767
;乘法：两位乘数、积范围均为：0~65536
;除法：被除数、除数、商、余数范围均为：0~32767
;'='--输出结果，'C'--归零
;--------------------------------------------------------------------------------
CRLF		MACRO					;显示回车和换行
		MOV AH,02H
		MOV DL,0DH
		INT 21H
		MOV AH,02H
		MOV DL,0AH
		INT 21H
		ENDM
STACK1	SEGMENT
	DB 256 DUP(?)
STACK1	ENDS
DATA 		SEGMENT
		RE DB 0,0,0,0,0,'$'		;计算结果的ASCII码
		DIVI DW 10000,1000,100,10,1 	;万、千、百、十、个
		SE DB 6 DUP('.'),'$'		;除法间隔符
		SSE DB 50 DUP('+'),0DH,0AH,'$';交互界面分隔
		STIP DB 'My Calculator:',0DH,0AH,'$';提示用户输入计算式
DATA		ENDS
CODE 		SEGMENT
	ASSUME CS:CODE,DS:DATA 
START:	MOV AX,DATA				;数据段
		MOV DS,AX
		MOV AX,STACK1			;栈段
		MOV SS,AX
		MOV AH,09H				;显示分割线
		LEA DX,SSE
		INT 21H
		MOV AH,09H				;显示提示词
		LEA DX,STIP
		INT 21H
REFRESH:	XOR AX,AX				;AX清零
		CALL INPUT				;输入第一个数	
		PUSH BX				;存入栈
		;判断运算符，跳转
		CMP AL,'+'				
		JZ CADD
		CMP AL,'-'				
		JZ CSUB
		CMP AL,'*'				
		JZ CMUL
		CMP AL,'/'				
		JZ CDIV
CADD:		CALL INPUT				;输入第二个数
		POP AX				;第一个数取出
		ADD AX,BX				;相加
		JMP NEXT				;跳出
CSUB:		CALL INPUT				;输入第二个数
		POP AX				;第一个数取出
		CMP AX,BX				;判断被减数与减数的大小关系
		JL LESS				;小于，跳转
		SUB AX,BX				;大于，直接相减
		JMP NEXT
LESS:		SUB AX,BX				;相减为负则取反
		NEG AX
		PUSH AX				;保护AX
		MOV DL,'-'				;输出负号
		MOV AH,02H
		INT 21H
		POP AX				;送回AX
		JMP NEXT				;跳出
CMUL:		CALL INPUT				;输入第二个数
		POP AX				;第一个数取出
		MUL BX				;相乘
		JMP NEXT				;跳出
CDIV:		CALL INPUT				;输入第二个数
		POP AX				;第一个数取出
		DIV BX				;相除
		CMP DX,0				;检测余数
		JZ NEXT				;直接跳出
		PUSH DX				;保护DX
		CALL OUTPUT				;输出商
		MOV AH,09H				;显示间隔符
		LEA DX,SE
		INT 21H
		POP DX				;送回DX
		MOV AX,DX				;输出余数
		CALL OUTPUT		
		JMP REFRESH				;跳出，刷新
NEXT:		CALL OUTPUT				;结果输出
		JMP REFRESH				;跳出，刷新
		MOV AH,4CH
		INT 21H

INPUT		PROC NEAR				;输入子程序
		MOV BX,0				;记录已输入的数值，初始化BX清零
INNUM:	MOV AH,01H				;字符输入
		INT 21H
		CMP AL,'C'				;归零跳转
		JZ CLEAR
		CMP AL,'+'				;运算符跳出
		JZ EXIT
		CMP AL,'-'				
		JZ EXIT
		CMP AL,'*'				
		JZ EXIT
		CMP AL,'/'				
		JZ EXIT
		SUB AL,30H				;ASCII码转换为十进制
		JL EXIT				;排除0~9以外的字符
		CMP AL,9
		JG EXIT
		CBW					;按数位依次将输入的运算数存入
		XCHG AX,BX				;已输入数值送入
		MOV CX,10				;十进制
		MUL CX				;十进制下左移一位
		XCHG AX,BX				;送回
		ADD BX,AX				;当前输入位加入
		JMP INNUM				;跳转输入下一位
CLEAR:	CRLF					;回车换行
		XOR AX,AX				;寄存器AX,BX清零	
		XOR BX,BX
		JMP INNUM				;跳转输入下一位
EXIT:		RET 
INPUT		ENDP

OUTPUT	PROC NEAR				;输出子程序
		MOV SI,OFFSET RE			;指针
		MOV DI,OFFSET DIVI
		MOV CX,5				;设置循环次数
LTRANS:	MOV DX,0				;DX清零,存储未转换数值
		DIV WORD PTR [DI]			;位数
		ADD AL,30H				;十进制转换为ASCII码
		MOV BYTE PTR [SI],AL		;存储
		INC SI				;指针步进
		ADD DI,2
		MOV AX,DX				;未转换值送回
		LOOP LTRANS
		MOV SI,OFFSET RE			;指针
		MOV CX,4				;设置循环次数
LPRINT:	CMP BYTE PTR [SI],30H		;从第一个有效位开始输出
		JNZ PRINT
		INC SI				;指针步进
		LOOP LPRINT
PRINT:	MOV DX,SI				;计算结果输出
		MOV AH,09H
		INT 21H
		RET 
OUTPUT	ENDP

CODE		ENDS
		END START 