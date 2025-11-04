#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "rfid_process.h"

#define IRQ_Slot_En 0x20
#define Eint0 14
#define Eint1 15
#define Eint2 16

volatile unsigned char sw1_flag = 0;
volatile unsigned char sw2_flag = 0;
volatile unsigned char sw3_flag = 0;
unsigned char mode = 0;

void EXT_INT0_ISR(void) __irq;
void EXT_INT1_ISR(void) __irq;
void EXT_INT2_ISR(void) __irq;

void config_intrpt(void) {
    PINSEL1 |= 0x01;          // EINT0
    PINSEL0 |= 0x20000000;    // EINT1
    PINSEL0 |= 0x80000000;    // EINT2

    VICIntSelect = 0;
    VICVectCntl0 = IRQ_Slot_En | Eint1;
    VICVectAddr0 = (unsigned int)EXT_INT1_ISR;
    VICVectCntl1 = IRQ_Slot_En | Eint2;
    VICVectAddr1 = (unsigned int)EXT_INT2_ISR;
    VICVectCntl2 = IRQ_Slot_En | Eint0;
    VICVectAddr2 = (unsigned int)EXT_INT0_ISR;

    VICIntEnable = (1 << Eint0) | (1 << Eint1) | (1 << Eint2) | (1 << 6);

    EXTMODE = 0;
    EXTPOLAR = 0;
}

void EXT_INT0_ISR(void) __irq {
    EXTINT = 0x01;
    sw3_flag = 1;
    VICVectAddr = 0;
}

void EXT_INT1_ISR(void) __irq {
    EXTINT = 0x02;
    sw1_flag = 1;
    VICVectAddr = 0;
}

void EXT_INT2_ISR(void) __irq {
    EXTINT = 0x04;
    sw2_flag = 1;
    VICVectAddr = 0;
}

