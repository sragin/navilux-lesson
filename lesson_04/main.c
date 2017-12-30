/* Simple C code for ARM925EJ-S Core by layright */
#include <stdio.h>

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTERS   0x18
#define SERIAL_TX_BUFFER_FULL (1 << 5)

void my_putc(char c);
void my_puts(const char *str);

void swiHandler(unsigned int syscallnum)
{
    char strTmp[100];
    sprintf(strTmp, "system call %d\n", syscallnum);
    my_puts(strTmp);
}

void irqHandler(void)
{

}

void my_putc(char c)
{
   /* Wait until the serial buffer is empty */
   while(*(volatile unsigned long*)(SERIAL_BASE + SERIAL_FLAG_REGISTERS) & (SERIAL_TX_BUFFER_FULL));
   /* Put our character into the serial buffer */
   *(volatile unsigned long*)SERIAL_BASE = c;
}

void my_puts(const char *str)
{
   while(*str)
   {
      my_putc(*str++);
   }
}

void msleep(int msec)
{
    for(; msec>0 ; msec--)
        for(int i=0; i < 85000; i++);
}

int main (void)
{
    while(1)
    {
        __asm__("swi 77");
        msleep(1000);
    }

    return 0;
}
