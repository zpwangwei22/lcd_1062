#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"


void delay_init();
void delay(u32 nms);
void delay_us(u32 nus);
void delay_s(u32 ns);



#endif





