;--------------------------------------------------------------------------------
;程序描述：
;	可实现多项式Z=(X+Y)*8/2在10位数以内的运算，不考虑除法溢出问题
;作者：周帆
;时间：2023年5月13日
;输入格式样例：
;	运行程序后，从键盘输入X的数值X=12，按下回车之后，从键盘输入Y的数值Y=34
;	系统运算得到运算式的结果并显示在屏幕上
;调试工具：
;	HQFC-A微机接口
;说明：无
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
		VX DB	10 DUP(?)			;预置变量X,Y,Z的存储空间
		VY DB 10 DUP(?)
		VR DB 12 DUP(?)			;中间变量
		VZ DB 13 DUP(?)
		SSE DB 50 DUP('+'),0DH,0AH,'$';交互界面分隔
		SPO DB 'Polynomial:Z=(X+Y)*8/2',0DH,0AH,'$';提示用户默认的多项式运算
		SVX DB 'X=',0DH,0AH,'$'		;提示用户输入X
		SVY DB 'Y=',0DH,0AH,'$'		;提示用户输入Y
		SVZ DB 'Z=',0DH,0AH,'$'		;输入结果Z
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
		MOV AH,09H				;显示运算式
		LEA DX,SPO
		INT 21H
		;输入变量X,并逆序存入数据段
		MOV AH,09H				;提示用户输入变量X
		LEA DX,SVX
		INT 21H
		MOV BX,0				;统计字节长
		MOV CX,10				;设置循环次数上限
		LEA SI,VX				;指针指向变量存储首地址
LIX1:		MOV AH,08H				;逐字输入
		INT 21H
		CMP AL,0DH				;检测，输入回车符表示输入完成
		JZ JIENDX				;完成，跳转
		MOV DL,AL				;显示
		MOV AH,02H
		INT 21H
		SUB AL,30H				;将ASCII码转换为十进制数，方便运算
		PUSH AX				;入栈
		INC BX				;计数
		LOOP LIX1
JIENDX:	CRLF
		MOV CX,BX				;设置循环次数为字节长
LIX2:		POP AX				;出栈
		MOV [SI],AL				;未完成，则将字符存入
		INC SI				;指针步进
		LOOP LIX2
		;输入变量Y,并逆序存入数据段
		MOV AH,09H				;提示用户输入变量Y
		LEA DX,SVY
		INT 21H
		MOV BX,0				;统计字节长
		MOV CX,10				;设置循环次数上限
		LEA SI,VY				;指针指向变量存储首地址
LIY1:		MOV AH,08H				;逐字输入
		INT 21H
		CMP AL,0DH				;检测，输入回车符表示输入完成
		JZ JIENDY				;完成，跳转
		MOV DL,AL				;显示
		MOV AH,02H
		INT 21H
		SUB AL,30H				;将ASCII码转换为十进制数，方便运算
		PUSH AX				;入栈
		INC BX				;计数
		LOOP LIY1
JIENDY:	CRLF
		MOV CX,BX				;设置循环次数为字节长
LIY2:		POP AX				;出栈
		MOV [SI],AL				;未完成，则将字符存入
		INC SI				;指针步进
		LOOP LIY2
		;计算及输出
		CALL CADD				;加法计算
		CALL CMUL				;乘法计算
		CALL CDIV				;除法计算
		CALL TRANS				;结果转换为ASCII码
		CALL ORESULT			;输出计算结果
		MOV AH,4CH
		INT 21H

CADD		PROC NEAR				;加法计算子程序
		PUSH SI				;保护现场
		PUSH DI
		PUSH BX
		PUSH CX
		PUSH AX
		LEA SI,VX				;指针SI指向变量X首地址
		LEA DI,VY				;指针DI指向变量Y首地址
		LEA BX,VR				;指针BX指向变量R首地址
		MOV CX,10				;设置循环次数
		XOR AX,AX				;AX清零
		CLC
LADD:		MOV AL,[SI]				;逐位相加
		ADC AL,[DI]
		AAA
		MOV [BX],AL				;存入结果
		INC SI				;指针步进
		INC DI
		INC BX				
		LOOP LADD
		JNC JEND
		MOV [BX],01H			;进位计入
JEND:		POP AX				;恢复现场
		POP CX	
		POP BX
		POP DI
		POP SI
		RET
CADD		ENDP

CMUL		PROC NEAR				;乘法计算子程序
		PUSH DX				;保护现场
		PUSH SI
		PUSH BX
		PUSH CX
		PUSH AX
		MOV DL,08H				;乘数
		LEA SI,VR				;指针SI指向变量R首地址
		MOV BL,00H				;存放进位
		MOV CX,12				;设置循环次数
		CLC
LMUL:		MOV AL,[SI]
		MUL DL				;逐位相乘
		AAM
		ADD AL,BL				;加入进位
		AAA
		MOV [SI],AL				;结果低四位存入AL
		MOV BL,AH				;进位存入BL
		XOR AX,AX				;AX清零 
		INC SI				;指针步进
		LOOP LMUL
		MOV [SI],BL				;存入进位
		POP AX				;恢复现场
		POP CX
		POP BX	
		POP SI
		POP DX
		RET
CMUL		ENDP

CDIV		PROC NEAR				;除法计算子程序
		PUSH DX				;保护现场
		PUSH DI
		PUSH SI
		PUSH AX
		PUSH CX
		MOV DL,02H				;存入除数
		LEA DI,VZ				;指针DI指向变量Z首地址
		LEA SI,VZ				;指针SI指向变量R末地址
		DEC SI
		MOV AH,[SI]				;AH装入
		MOV AL,00H				;AL清零
		DEC SI
		INC DI
		MOV CX,11				;设置循环次数(将第0、1位装入AX，避免除法溢出）
		CLC
LDIV:		MOV AL,[SI]				;取出变量Z的字节
		AAD
		DIV DL				;逐位相除
		MOV [DI],AL				;结果低四位存入AL
		XOR AL,AL				;AL清零 
		DEC SI				;指针步退
		INC DI				;指针步进
		LOOP LDIV
		POP CX				;恢复现场
		POP AX	
		POP SI
		POP DI
		POP DX
		RET
CDIV		ENDP

TRANS		PROC NEAR				;将加法计算结果转换为ASCII码
		PUSH SI				;保护现场
		PUSH AX
		LEA SI,VZ				;指针指向存储首地址
		MOV CX,12				;设置循环次数
LTRANS:	MOV AL,[SI]
		ADD AL,30H
		MOV [SI],AL
		INC SI				;指针步进
		LOOP LTRANS
		MOV [SI],'$'			;字符串结束标识符存入
		POP AX				;恢复现场
		POP SI
		RET
TRANS		ENDP

ORESULT	PROC NEAR				;将计算结果输出到屏幕
		PUSH AX				;保护现场
		PUSH DX
		MOV AH,09H				;提示输出结果
		LEA DX,SVZ
		INT 21H
		MOV CX,12				;设置循环次数
		LEA SI,VZ				;指针指向结果Z
LO:		MOV DL,[SI]
		MOV AH,02H				;输出结果
		INT 21H
		INC SI				;指针步进
		LOOP LO
		CRLF
		POP DX				;恢复现场
		POP AX	
		RET
ORESULT	ENDP

CODE		ENDS
		END START 