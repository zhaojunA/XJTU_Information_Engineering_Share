data segment
	io8255a	equ	280h   
	io8255c	equ	282h   
	cotl8255	equ   283h  ;A、C和控制口的地址
data ends

code segment
	assume cs:code
start:
	mov ax,data
	mov ds,ax
	mov es,ax
main:
	mov dx,cotl8255		;设置A口为输入口，C口为输出口
	mov al,90h			;8255控制字
	out dx,al
inout: 
	mov dx,io8255a		;从A口输入一数据
	in  al,dx			;数据存放到AL中
	mov dx,io8255c 		;从C口读取一个数据
	out dx,al 			;将读取的数据输出
	jmp inout 			;若无，则继续从C口输入，从A口输出
code ends
	end start