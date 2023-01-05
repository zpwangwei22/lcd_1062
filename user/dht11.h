#ifndef __DHT11_H
#define __DHT11_H

#include"stm32f10x.h"
#include"delay.h"

#define DataPort    GPIOB
#define DataPin     GPIO_Pin_0

uint8_t read_dht11_byte(void);
uint8_t read_dht11_value(void);
void set_port_output(void);
void dht11_init(void);
void set_port_input(void);

#endif







