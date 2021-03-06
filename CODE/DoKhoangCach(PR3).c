//PIC16F877A - HC-SR04
//NguyenDucThang_101183
 
#include <16F877A.h>
#device *=16 adc=10

#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20M)

#include <lcd.h>

#define TRIG      PIN_B0
#define ECHO      input(PIN_B1)
#define BUTTON    input(PIN_A3)

float DoKhoangCach(void);


void main()
{
   float Value;
   lcd_init();
   lcd_putc('\f');
   lcd_gotoxy(1,1);
   printf(lcd_putc,"NGUYEN DUC THANG");
   delay_ms(5000);
   lcd_gotoxy(1,2);
   printf(lcd_putc,"          TK16.3");
   delay_ms(5000);
   lcd_gotoxy(1,1);
   lcd_putc('\f');
   printf(lcd_putc,"     DO AN 3    ");
   delay_ms(5000);
   lcd_gotoxy(1,2);
   printf(lcd_putc," THUOC DIEN TU  ");
   delay_ms(8000);
   lcd_gotoxy(1,2);
   printf(lcd_putc,"NHAN ST DE DO KC");
   delay_ms(5000);
   int8 check = 0;
   while(TRUE)
   {   
      if(input(PIN_A3)==0)
      {        
         Value = DoKhoangCach();
            
         if (Value >= 224 || Value <= 2.5)
         {
            check = 1;
         }
         if (Value < 224)
         {
            check = 0;
         }
         
         if (check == 1)
         {
            lcd_gotoxy(1,1);
            printf(lcd_putc,"NGOAI PHAM VI DO");
            lcd_gotoxy(1,2);
            printf(lcd_putc,"                ");        
            delay_ms(100);
         }
         
         if (check == 0) 
         {
            lcd_gotoxy(1,1);
            printf(lcd_putc,"   KHOANG CACH     ");
            lcd_gotoxy(1,2);
            printf(lcd_putc,"   >>>%.1f cm         \r\n",Value);        
            delay_ms(100);
         }
      }
   }
}

float DoKhoangCach(void)
{
   float Value;
   int16 Time;
   
   output_high(TRIG);
   delay_ms(10);
   output_low(TRIG);
   
   while(ECHO==0);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   set_timer1(0);
   while(ECHO==1);
   setup_timer_1(T1_DISABLED);
   Time = get_timer1();
   
//!T = 4 * (1/Fosc) * (Prescale)
//!  = 4 * (1/20) * 1
//!  = 0.2(us)=1/5us
//!=> Tmax = 1 * (2^16) = 65536(us)   
   
   Value = (float)Time/58.0f;
   Value = Value*0.2f;
   
   return Value;
}

