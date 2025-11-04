#include <lpc21xx.h>
#include <string.h>
#include "lcd.h"
#include "delay.h"
#include "rfid_process.h"

#define IRQ_Slot_En 0x20

extern unsigned char mode;
char rfid_data[13];

void uart0_ISR(void) __irq;

void uart0_configure(void) {
    PINSEL0 |= 0x05;    // P0.0=TXD0, P0.1=RXD0
    U0LCR = 0x83;
    U0DLL = 97;         // 9600 baud for 12MHz PCLK
    U0DLM = 0;
    U0LCR = 0x03;
    U0IER = 0x01;       // Enable RBR interrupt
    VICVectCntl4 = IRQ_Slot_En | 6;
    VICVectAddr4 = (unsigned int)uart0_ISR;
}

void uart0_ISR(void) __irq {
    static unsigned char i = 0;
    unsigned char temp;

    if (U0IIR & 0x04) {
        temp = U0RBR;
        if (i == 0) memset(rfid_data, 0, sizeof(rfid_data));
        if (i < 12) rfid_data[i++] = temp;

        if (i == 12) {
            rfid_data[i] = '\0';
            lcd_command(0x01);

            if (mode == 0)
                display_tag_and_price(rfid_data);
            else if (mode == 1 || mode == 2)
                process_rfid(rfid_data);

            delay_ms(1500);
            lcd_command(0x01);
            lcd_command(0x80);
            lcd_str("Show the Tag");
            i = 0;
        }
    }
    VICVectAddr = 0;
}

