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
   b IRQ      /* Fast Interrupt : Stay Here        */

.equ svc_stack, 0x7A80000
.equ irq_stack, 0x7B00000
.equ sys_stack, 0x7B80000
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

   bl  main   /* Jump to main function (C code) */
   b _start   /* Jump to _reset if kernel return */

swi:
    stmfd   sp!, {r0-r12,r14}
    mrs     r1, spsr
    stmfd   sp!, {r1}
    ldr     r0, [lr, #-4]
    bic     r0, r0, #0xff000000
    bl      swiHandler
    ldmfd   sp!, {r1}
    msr     spsr_cxsf, r1
    ldmfd   sp!, {r0-r12,pc}^

IRQ:
    sub     lr, lr, #4
    stmfd   sp!, {lr}
    stmfd   sp!, {r0-r14}^
    mrs     r1, spsr
    stmfd   sp!, {r1}
    bl      irqHandler
    ldmfd   sp!, {r1}
    msr     spsr_cxsf, r1
    ldmfd   sp!, {r0-r14}^
    ldmfd   sp!, {pc}^

