/* Simple C code for ARM925EJ-S Core by layright */

#define SERIAL_BASE 0x16000000
#define SERIAL_FLAG_REGISTERS   0x18
#define SERIAL_TX_BUFFER_FULL (1 << 5)

void my_putc (char c);
void my_puts (const char *str);
int my_main (void);

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

int my_main (void)
{
    while(1)
    {
        my_puts ("Hello World!\n");
        for(int i=0;i < 10000000; i++);
    }

    return 0;
}
