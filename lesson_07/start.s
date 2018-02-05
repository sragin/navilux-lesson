/* Simple Start Up code for ARM925EJ-S Core by layright */
/* Modified by sragin */ 
.text
.code 32

.global _start
.func   _start

   /* ############################################ */
   /* #             Vector Table                 # */
   /* ############################################ */
_start:
   b kernel_init /* Reset : Branch to _reset function */
   b .        /* Undefined Instruction : Stay here */
   b swi      /* Software Interrupt : Stay here    */
   b .        /* Prefetch Abort : Stay here        */
   b .        /* Data Abort : Stay here            */
   b .        /* Reserved : Stay Here              */
   b IRQ      /* Normal Interrupt : Stay Here      */
   b _start   /* Fast Interrupt : Reset            */

/* 각각 512K씩 스택 공간을 확보함 0x80000 = 512K */
.equ svc_stack, 0x0300000
.equ irq_stack, 0x0380000
.equ sys_stack, 0x0400000 /* 0x0400000 = 4MB */
.global kernel_init
kernel_init:
	ldr		sp, =stack_top // stack size = 4MB (0x40,0000)

	msr		cpsr_c, #0xc0|0x13	//SVC mode
	ldr		r0, =svc_stack
	sub		sp, r0, #4

	msr		cpsr_c, #0xc0|0x12	//IRQ mode
	ldr		r0, =irq_stack
	sub		sp, r0, #4

	msr		cpsr_c, #0xc0|0x1f	//SYSTEM mode
	ldr		r0, =sys_stack
	sub		sp, r0, #4

	msr		cpsr_c, #0xc0|0x13

	bl		main   /* Jump to main function (C code) */
	b		_start   /* Jump to _reset if kernel return */

swi:
    stmfd   sp!, {r0-r12,r14}
    ldr     r0, [lr, #-4]
    bic     r0, r0, #0xff000000
    bl      swiHandler
    ldmfd   sp!, {r0-r12,pc}^

IRQ:
    sub     lr, lr, #4
    stmfd   sp!, {r0-r12,lr}
    bl      irqHandler
    ldmfd   sp!, {r0-r12,pc}^

