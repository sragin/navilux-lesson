/* Link script for ARM925EJ-S Core by layright */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY (_start)

MEMORY
{
    ram (rwx) : ORIGIN = 0x00000000, LENGTH = 0x00100000
}
SECTIONS
{
   . = 0x0;
   .text :
   {
      *start.o(.text)
      *main.o(.text)
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

    /* Stack starts at end of ram */
    _estack = ORIGIN(ram) + LENGTH(ram) - 4;
}
