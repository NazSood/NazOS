		AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
		PRESERVE8
		EXTERN  currentPt
		EXPORT	SysTick_Handler
		EXPORT  osSchedulerLaunch
	    IMPORT  osSchedulerRoundRobin


SysTick_Handler          ;save r0,r1,r2,r3,r12,lr,pc,psr      
    CPSID   I                  
    PUSH    {R4-R11}        ;save r4,r5,r6,r7,r8,r9,r10,r11   
    LDR     R0, =currentPt  ; r0 points to currentPt       
    LDR     R1, [R0]        ; r1= currentPt   
    STR     SP, [R1]           
    ;LDR     R1, [R1,#4]     ; r1 =currentPt->next   
    ;STR     R1, [R0]        ;currentPt =r1   
    PUSH	{R0,LR}
	BL      osSchedulerRoundRobin
	POP		{R0,LR}
	LDR		R1,[R0]          ;R1= currentPt i.e. New thread
	LDR     SP, [R1]        ;SP= currentPt->stackPt   
    POP     {R4-R11}           
    CPSIE   I                  
    BX      LR 
	

osSchedulerLaunch
    LDR     R0, =currentPt         
    LDR     R2, [R0]       ; R2 =currentPt       
    LDR     SP, [R2]       ;SP = currentPt->stackPt    
    POP     {R4-R11}          
    POP     {R0-R3}            
    POP     {R12}
    ADD     SP,SP,#4           
    POP     {LR}               
    ADD     SP,SP,#4         
    CPSIE   I                 
    BX      LR                 

    ALIGN
    END
		
		