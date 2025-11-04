#include <lpc21xx.h>
#include <string.h>
#include <stdio.h>
#include "lcd.h"
#include "uart.h"
#include "interrupt.h"
#include "rfid_process.h"
#include "delay.h"

extern volatile unsigned char sw1_flag, sw2_flag, sw3_flag;
extern unsigned char mode;

int main() {
    lcd_init();
    uart0_configure();
    config_intrpt();

    lcd_command(0x80);
    lcd_str("V24ce9r1");
    lcd_command(0xC0);
    lcd_str("SMART TROLLEY");
    delay_ms(1500);

    lcd_command(0x01);
    lcd_command(0x80);
    lcd_str("Show the Tag");

    while (1) {
        if (sw1_flag) {
            sw1_flag = 0;
            mode = 1;
            lcd_command(0x01);
            lcd_command(0x80);
            lcd_str("Mode Selected");
            lcd_command(0xC0);
            lcd_str("Add:show Tag");
            delay_ms(500);
        }

        if (sw2_flag) {
            sw2_flag = 0;
            mode = 2;
            lcd_command(0x01);
            lcd_command(0x80);
            lcd_str("Mode Selected");
            lcd_command(0xC0);
            lcd_str("Remove:show Tag");
            delay_ms(500);
        }

        if (sw3_flag) {
            sw3_flag = 0;
            mode = 3;
            lcd_command(0x01);
            lcd_command(0x80);
            lcd_str("Mode Selected");
            lcd_command(0xC0);
            lcd_str("Total");
            delay_ms(500);
            show_total();
        }
    }
}

