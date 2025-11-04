#ifndef __LCD_4BIT_H__
#define __LCD_4BIT_H__

void LCD_INITI(void);
void LCD_COMMAND(unsigned char cmd);
void LCD_DATA(unsigned char d);
void LCD_str(unsigned char *s);
void LCD_int(int n);
void LCD_float(float f);

#endif

