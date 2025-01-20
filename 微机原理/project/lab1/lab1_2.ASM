CODE    SEGMENT          ;在内存指定单元建立十进制数
	    ASSUME CS:CODE
	    ORG 2000H	        ;程序起始地址
START:  MOV DI,1000H	 ;设数据区首址 
        MOV CX,0010H    ;字节数→ CX
        MOV AX,000FH    ;000F → AX
	  DAA			;十进制调整，变为00 00 00 15
CNT:    MOV [DI],AL     ;（AL）→ [DI]
        INC DI          ;修改地址指针
        SUB AL,01       ;修改数据，AL-1
        DAS             ;十进制调整，减法调整DAS
        LOOP CNT        ;未填完，继续
        JMP $           ;填完，结束
CODE    ENDS
        END  START
 