io8254a 	equ 283h	;控制口
io8254b 	equ 280h	;计数器0的地址
io8254c 	equ 281h	;计数器1的地址
code segment
	assume cs:code
start: 
	mov 	al,14h 	;设置8254通道0为工作方式2,二进制计数
	mov 	dx,io8254a
	out 	dx,al
	mov 	dx,io8254b 	;送计数初值为08H
	mov 	al,8H
	out 	dx,al
code ends
	end start