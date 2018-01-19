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
    sprintf(strTmp, "system call %d\n\r", syscallnum);
    my_puts(strTmp);
}

#define PIC_IRQ_STATUS	((volatile unsigned long int*)0x14000000)
#define TIMERINT1		6
#define TIMER1_ICR 		((volatile unsigned long int*)0x1300010C)

void irqHandler(void)
{
	unsigned long int pic_irq_status = *PIC_IRQ_STATUS;

	if (pic_irq_status)
	{
		if (pic_irq_status == (1 << TIMERINT1))
		{
			my_puts("timer1 interrupt\n\r");
			// clear interrupt
    		*TIMER1_ICR = 1;
		}
	}
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

#define PIC_IRQ_ENSET ((volatile unsigned long int*)0x14000008)
#define PIC_IRQ_ENCLR ((volatile unsigned long int*)0x1400000C)
#define TIMER1_LOAD ((volatile unsigned long int*)0x13000100)
#define TIMER1_CTRL ((volatile unsigned long int*)0x13000108)

void timer1_init(void)
{
	char strTmp[100];
    *PIC_IRQ_ENCLR = (1 << TIMERINT1);
    *TIMER1_ICR = 1;
    *PIC_IRQ_ENSET |= (1 << TIMERINT1);
	sprintf(strTmp, "PIC_IRQ_ENSET = 0x%lx\n\r", *PIC_IRQ_ENSET);
	my_puts(strTmp);
    
    *TIMER1_LOAD = 1000000;
    *TIMER1_CTRL |= (1 << 6) | (0x00 << 2) | (1 << 1) | (0 << 0); 
}    

void timer1_start(void)
{
    *TIMER1_CTRL |= (1 << 7) | (1 << 5);
}

void irq_enable(void)
{
    __asm__("msr    cpsr_c, #0x40|0x13");
}

void irq_disable(void)
{
    __asm__("msr    cpsr_c, #0xc0|0x13");
}

int main (void)
{
	my_puts("init\n\r");
	timer1_init();
	my_puts("start\n\r");
    timer1_start();

	my_puts("irq en\n\r");
    irq_enable();

    while(1)
    {
        __asm__("swi 77");
        msleep(1000);
    }

    return 0;
}
