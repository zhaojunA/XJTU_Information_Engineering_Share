.data@数据段
xx:
.byte 6 

.text@代码段
.global _start @程序入口
_start:
ldr x1,#xx@将变量xx赋值给x1寄存器 
mov x2,2@将立即数赋值给x2寄存器
lsl x0,x1,x2@将x1寄存器的数值左移x2数值，然后赋值给x0.
.end




