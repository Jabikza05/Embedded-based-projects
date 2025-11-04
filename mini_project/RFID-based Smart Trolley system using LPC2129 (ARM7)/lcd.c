#include <LPC21XX.H>
#include "delay.h"

#include"lcd.h"
#define lcd_d 0xF<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

void LCD_INITI(void)
{
	 IODIR1=lcd_d|RS|E|RW;
	 IOCLR1=RW;
	 LCD_COMMAND(0x01);
	 LCD_COMMAND(0x02);
	 LCD_COMMAND(0x0C);
	 LCD_COMMAND(0x28);
	
	
}


void LCD_COMMAND(unsigned char cmd )
{      
	IOCLR1=lcd_d;
	IOSET1=(cmd&0xf0)<<16;
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=lcd_d;
	IOSET1=(cmd&0x0f)<<20;
	IOCLR1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}


void LCD_DATA(unsigned char d )
 {

	IOCLR1=lcd_d;
	IOSET1=(d&0xf0)<<16;
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;

	IOCLR1=lcd_d;
	IOSET1=(d&0x0f)<<20;
	IOSET1=RS;
	IOSET1=E;
	delay_ms(2);
	IOCLR1=E;
}

 void LCD_str(unsigned char *s)
 {
	  
    while(*s)
		{
      LCD_DATA(*s++);
		
   }

}
  void LCD_int (int n)
{
    unsigned char a[5];
	  signed char i=0;
	if (n==0)
	LCD_DATA('0');
	else 	
	{
		if (n<0)
		{
		LCD_DATA ('-');
		n=-n;
    }
   
	while(n>0)
	{
    a[i++]=n%10;
		n=n/10;
	
  }
     for(--i;i>=0;i--)
	   LCD_DATA(a[i]+48);
  }
}
 
 
 void LCD_float (float f)
{
	
	int temp;
	temp=f;
	LCD_int(temp);
	LCD_DATA('.');
	temp=(f-temp)*100;
	LCD_int(temp);
}

  








        




 
 
 
 
