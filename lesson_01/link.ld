/* Link script for ARM925EJ-S Core by layright */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY (_start)

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
}
