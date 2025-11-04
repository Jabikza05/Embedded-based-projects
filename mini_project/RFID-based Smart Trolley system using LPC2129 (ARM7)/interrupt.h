#ifndef INTERRUPT_H
#define INTERRUPT_H

void config_intrpt(void);

extern volatile unsigned char sw1_flag;
extern volatile unsigned char sw2_flag;
extern volatile unsigned char sw3_flag;
extern unsigned char mode;

#endif

