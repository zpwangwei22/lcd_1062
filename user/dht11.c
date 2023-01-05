#include"dht11.h"


uint8_t DHT_Val[5] = {0x00, 0x00, 0x00, 0x00,0x00};
uint8_t sum = 0;

void dht11_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void set_port_output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = DataPin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(DataPort, &GPIO_InitStruct);
}

void set_port_input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = DataPin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(DataPort, &GPIO_InitStruct);
}

uint8_t read_dht11_byte(void)
{
    uint8_t tmp;
    uint8_t ReadData = 0x00;
    uint8_t retry = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        while(GPIO_ReadInputDataBit(DataPort, DataPin)==0 && retry < 100)
        {
            retry++;
            delay_us(1);
        }
        retry = 0;
        delay_us(35);
        tmp = 0;
        if(GPIO_ReadInputDataBit(DataPort, DataPin) == 1)
        {
            tmp = 1;
        }
        while(GPIO_ReadInputDataBit(DataPort, DataPin)==1 && retry < 50)
        {
            retry++;
            delay_us(1);
        }
        retry = 0;
        ReadData <<= 1;
        ReadData |= tmp;
    }
    return ReadData;
}

uint8_t read_dht11_value(void)
{
    uint8_t retry = 0;
    set_port_output();
    GPIO_ResetBits(DataPort, GPIO_Pin_0);
    delay(20);
    GPIO_SetBits(DataPort, GPIO_Pin_0);
    delay_us(40);
    set_port_input();
    delay_us(20);
    if(GPIO_ReadInputDataBit(DataPort, DataPin) == 0)
    {
        while(GPIO_ReadInputDataBit(DataPort, DataPin) ==0 && retry < 100)
        {
            retry++;
            delay_us(1);
        }
        retry = 0;
        while(GPIO_ReadInputDataBit(DataPort, DataPin) == 1 && retry < 100)
        {
            retry++;
            delay_us(1);
        }
        retry = 0;
        for(uint8_t i = 0; i < 5; i++)
        {
            DHT_Val[i] = read_dht11_byte();
        }
        delay_us(50);
    }

    sum = DHT_Val[0] + DHT_Val[1] + DHT_Val[2] + DHT_Val[3];
    if(sum == DHT_Val[4])
    {
        return 1;
    }
    else
        return 0;

}




