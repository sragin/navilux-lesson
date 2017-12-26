/* LCD Example code for ARM925EJ-S Core by layright */
typedef unsigned char      UINT8;
typedef signed   char      INT8;
typedef unsigned short     UINT16;
typedef signed   short     INT16;
typedef unsigned int       UINT32;
typedef signed   int       INT32;
typedef unsigned long      ULONG;
typedef signed   long      LONG;
typedef unsigned long long ULONG64;
typedef signed   long long LONG64;

#define PL110_LCD_IO_BASE      0xC0000000

typedef struct _PL110MMIO
{
   volatile UINT32 tim0;   /* LCDTiming0 : 0xC0000000 (Horizontal Axis Panel Control Register)      */
   volatile UINT32 tim1;   /* LCDTiming1 : 0xC0000004 (Veritical Axis Panel Control Register)       */
   volatile UINT32 tim2;   /* LCDTiming2 : 0xC0000008 (Clock and Signal Polarity Control Register)  */
   volatile UINT32 tim3;   /* LCDTiming3 : 0xC000000C (Line End Control Register)                   */
   volatile UINT32 ubase;  /* LCDUPBASE  : 0xC0000010 (Upper and Lower Panel Frame Base Addr. Reg.) */
   volatile UINT32 lbase;  /* LCDLPBASE  : 0xC0000014 (Upper and Lower Panel Frame Base Addr. Reg.) */
   volatile UINT32 imask;  /* LCDIMSC    : 0xC0000018 (Interrupt Mask Set/Clear Register)           */
   volatile UINT32 ctrl;   /* LCDControl : 0xC000001C (Control Register)                            */
} PL110MMIO;

int my_main (void);
void draw_line (UINT16 start, INT8 *ptr);

int my_main (void)
{
   PL110MMIO   *lcd_io;
   UINT16       start;
   UINT32      loop;
   INT8        logo1[30] = "1   1                        X";
   INT8        logo2[30] = "1   1          3   4         X";
   INT8        logo3[30] = "1   1          3   4         X";
   INT8        logo4[30] = "1   1   222    3   4     555 X";
   INT8        logo5[30] = "11111  2   2   3   4    5   5X";
   INT8        logo6[30] = "1   1  2   2   3   4    5   5X";
   INT8        logo7[30] = "1   1  22222   3   4    5   5X";
   INT8        logo8[30] = "1   1  2       3   4    5   5X";
   INT8        logo9[30] = "1   1   222    3   4     555 X";

   /* Step 1 : Set PL110 LCD IO base */
   lcd_io = (PL110MMIO *)PL110_LCD_IO_BASE;

   /* Step 2 : Set Horizontal Axis Panel Control Register, LCDTiming0 (0xC0000000) */
   lcd_io->tim0 = 0x3F1F3F4C; /* 320 pixel */

   /* Step 3 : Set Vertical Axis Panel Control Register, LCDTiming1 (0xC0000004) */
   lcd_io->tim1 = 0x080B60EF; /* 240 pixel */

   /* Step 4 : Set Base Address of the frame buffer within SSRAM */
   lcd_io->ubase = 0x200000;

   /* Step 5 : Enable Color TFT LCD (16bpp) */
   lcd_io->ctrl = 0x00001829;

   /* Step 6 : Draw Hello */

   /* Step 6-1 : 1st line */
   start = (320 * 80) + 100;
   draw_line (start, &logo1[0]);

   /* Step 6-2 : 2nd line */
   start = (320 * 81) + 100;
   draw_line (start, &logo2[0]);

   /* Step 6-3 : 3rd line */
   start = (320 * 82) + 100;
   draw_line (start, &logo3[0]);

   /* Step 6-4 : 4th line */
   start = (320 * 83) + 100;
   draw_line (start, &logo4[0]);

   /* Step 6-5 : 5th line */
   start = (320 * 84) + 100;
   draw_line (start, &logo5[0]);

   /* Step 6-6 : 6th line */
   start = (320 * 85) + 100;
   draw_line (start, &logo6[0]);

   /* Step 6-7 : 7th line */
   start = (320 * 86) + 100;
   draw_line (start, &logo7[0]);

   /* Step 6-8 : 8th line */
   start = (320 * 87) + 100;
   draw_line (start, &logo8[0]);

   /* Step 6-9 : 9th line */
   start = (320 * 88) + 100;
   draw_line (start, &logo9[0]);

   return 0;
}

void draw_line (UINT16 start, INT8 *ptr)
{
   UINT16 loop;
   UINT16 *lcd_ptr;

   lcd_ptr = (UINT16 *)0x200000;

   for (loop = 0; loop < 30; loop++)
   {
      switch (ptr[loop])
      {
         case 0x31: /* 1 */
            *(lcd_ptr + start + loop) = 0xFFFF;
         break;

         case 0x32: /* 2 */
            *(lcd_ptr + start + loop) = 0xEEEE;
         break;

         case 0x33: /* 3 */
            *(lcd_ptr + start + loop) = 0xDDDD;
         break;

         case 0x34: /* 4 */
            *(lcd_ptr + start + loop) = 0xCCCC;
         break;

         case 0x35: /* 5 */
            *(lcd_ptr + start + loop) = 0xBBBB;
         break;

         default:
         break;
      }
   }
}
