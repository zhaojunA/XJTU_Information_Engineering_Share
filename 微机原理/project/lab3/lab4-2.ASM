io8254a 	equ 280h		;计数器0的地址
io8254b 	equ 281h		;计数器1的地址
io8254c 	equ 283h		;控制口地址
code segment
	assume cs:code
start:
	mov 	dx,io8254c 		;向8254写控制字
	mov 	al,36h 		;设置80540通道为工作方式3，先低后高传送计数器
	out 	dx,al
	mov 	ax,1000 		;写入循环计数初值1000
	mov 	dx,io8254a
	out 	dx,al 		;先写入低字节
	mov 	al,ah
	out 	dx,al 		;后写入高字节
	mov 	dx,io8254c
	mov 	al,76h 		;设8254通道1工作方式，先低后高传送计数器值
	out 	dx,al
	mov 	ax,1000 		;写入循环计数初值1000
	mov 	dx,io8254b
	out 	dx,al 		;先写低字节
	mov 	al,ah
	out 	dx,al 		;后写高字节
	mov 	ah,4ch 		;程序退出
	int 	21h
code ends
	end start

;经过两级1000分频，8254工作在方式3下，1MHz的脉冲被分为1Hz的方波，通过调整计数初值可以调整方波频率
;计算公式为f=fc/(M0*M1)，fc为时钟频率，M0和M1为计数器0和计数器1的计数初值，即分频系数