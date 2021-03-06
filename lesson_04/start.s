/* Simple Start Up code for ARM925EJ-S Core by layright */

.text
.code 32

.global _start
.func   _start

   /* ############################################ */
   /* #             Vector Table                 # */
   /* ############################################ */
_start:
   b _reset   /* Reset : Branch to _reset function */
   b .        /* Undefined Instruction : Stay here */
   b software_interrupt     /* Software Interrupt : Stay here    */
   b .        /* Prefetch Abort : Stay here        */
   b .        /* Data Abort : Stay here            */
   b .        /* Reserved : Stay Here              */
   b IRQ					/* Normal Interrupt : Stay Here      */
   b _reset		/* Fast Interrupt : Branch to _reset function */

.comm stack, 0x10000 @ Reserve 64K stack in the BSS

   /* ############################################ */
   /* #             Reset Function               # */
   /* ############################################ */
_reset:
   ldr sp, =stack+0x10000 /* Set up the stack      */
   bl  main   /* Jump to main function (C code) */
   b _reset   /* Jump to _reset if kernel return */

software_interrupt:
    PUSH	{r0-r12,r14}
    ldr     r0, [lr, #-4]
    bic     r0, r0, #0xff000000
    bl      swiHandler
    LDMFD	sp!,{r0-r12,pc}^

IRQ:
    b irqHandler
