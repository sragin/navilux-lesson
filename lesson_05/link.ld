/* Link script for ARM925EJ-S Core by layright */
/* Modified by sragin */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY (_start)

MEMORY
{
	/* default RAM size is 128M on QEMU */
    RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x8000000
}
SECTIONS
{
   . = 0x0;
   .text :
   {
      *start.o(.text)
	  *(.text*)
      *(.rodata*)
   }
   .data :
   {
       *(.data*)
   }
   .bss :
   {
       *(.bss*)
       *(COMMON*)
   }
    . = ALIGN(4);
    /* End of user data. Heap starts from hear */
    end = .;
	stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
