#ifndef __LCD_1602_H
#define __LCD_1602_H

#include"stm32f10x.h"
#include"delay.h"

#define EN_H    GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define EN_L    GPIO_ResetBits(GPIOA, GPIO_Pin_0)

#define RS_H    GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define RS_L    GPIO_ResetBits(GPIOA, GPIO_Pin_2)

#define RW_H    GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define RW_L    GPIO_ResetBits(GPIOA, GPIO_Pin_3)


void lcd_user_config();
void lcd_show_init();
void send_cmd2_lcd(uint8_t cmd);
void send_data2_lcd(uint8_t data);
void lcd_set_cur(uint8_t x, uint8_t y);
void send_str2_lcd(uint8_t x, uint8_t y, char *str);

#endif








