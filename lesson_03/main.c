/* Simple C code for ARM925EJ-S Core by layright */
#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTERS   0x18
#define SERIAL_TX_BUFFER_FULL (1 << 5)

void my_putc (char c);
void my_puts (const char *str);

void swiHandler(unsigned int syscallnum)
{
    //char strTmp[20];
    //sprintf(strTmp, "system call %d\n", syscallnum);
    //my_puts(strTmp);    
    my_puts("system call\n");
}

void irqHandler(void)
{

}

void my_putc (char c)
{
   /* Wait until the serial buffer is empty */
   while (*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTERS) & (SERIAL_TX_BUFFER_FULL));
   /* Put our character into the serial buffer */
   *(volatile unsigned long*)SERIAL_BASE = c;
}

void my_puts (const char *str)
{
   while (*str)
   {
      my_putc (*str++);
   }
}

int main (void)
{
    __asm__("swi 77");
    return 0;
}
