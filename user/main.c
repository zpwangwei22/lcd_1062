#include"head.h"


int main()
{
    char Tmp[16] = {0};
    char Hmd[16] = {0};
    dht11_init();
    delay_init();
    lcd_user_config();
    lcd_show_init();
    my_usart_init();

    while(1)
    {
        
        if(read_dht11_value())
        {
            printf("Hmd: %d%% Tmp: %d\n\r", DHT_Val[0], DHT_Val[2]);
            sprintf(Tmp,"Tmp: %d",DHT_Val[2]);
            send_str2_lcd(0, 0, Tmp);
            sprintf(Hmd,"Hmd: %d%%",DHT_Val[0]);
            send_str2_lcd(0, 1, Hmd);

            
        }
        delay_s(5);
    }
}






