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
   b .        /* Software Interrupt : Stay here    */
   b .        /* Prefetch Abort : Stay here        */
   b .        /* Data Abort : Stay here            */
   b .        /* Reserved : Stay Here              */
   b .        /* Normal Interrupt : Stay Here      */
   b .        /* Fast Interrupt : Stay Here        */

.comm stack, 0x10000 @ Reserve 64K stack in the BSS

   /* ############################################ */
   /* #             Reset Function               # */
   /* ############################################ */
_reset:
   ldr sp, =stack+0x10000 /* Set up the stack      */
   bl  my_main   /* Jump to main function (C code) */
1:
   b 1b      /* Backward branch : Stay here        */
