data segment   
	io8255a   	equ   28ah   
	cotl8255   	equ   28bh
	state 	db 	24h,44h,04h,44h,04h,44h,04h	;南北绿灯，东西红灯，之后黄灯闪烁
			db	81h,82h,80h,82h,80h,82h,80h	;南北红灯，东西绿灯，之后黄灯闪烁
			db	0ffh					;结束
data ends

code segment
	assume cs:code,ds:data
start:
	mov 	ax,data
	mov 	ds,ax
	mov 	dx,cotl8255
	mov 	al,90h		;控制字90h
	out 	dx,al 		;设置8255为C口输出
	mov 	dx,io8255a
re_on:
	mov 	bx,0
on:
	mov 	al,state[bx]
	cmp 	al,0ffh
	jz  	re_on			;结束标识符到来跳转
	out 	dx,al 		;点亮相应的灯
	inc 	bx
	mov 	cx,50 		;参数赋初值
	test 	al,21h 		;是否有绿灯亮
	jz 	de1 			;没有,短延时
	mov 	cx,1000 		;有,长延时
de1: 
	mov 	di,6000 		;di赋初值6000
de0: 
	dec 	di 			;减1计数
	jnz 	de0 			;di不为0
	loop 	de1
	push 	dx
	mov 	ah,06h
	mov 	dl,0ffh
	int 	21h
	pop 	dx			;返回系统
	jz 	on 			;没有,转到on
exit: 
	mov 	ah,4ch 		;返回
	int 	21h
code ends
	end start
