CODE    SEGMENT          ;在内存指定单元建立十进制数
	    ASSUME CS:CODE
	    ORG 2000H	        ;程序起始地址
START:  MOV DI,3500H	 ;设数据区首址 
        MOV CX,0010H    ;字节数→ CX
        MOV AX,0000     ; 0000 → AX
CNT:    MOV [DI],AL     ;（AL）→ [DI]
        INC DI          ;修改地址指针
        ADD AL,01       ;修改数据
        DAA              ;十进制调整
        LOOP CNT         ;未填完，继续
        JMP $            ;填完，结束
CODE    ENDS
        END  START
 