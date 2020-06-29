#include "interface.h"
#include "lcd/lcd.h"
#include "gd32vf103_gpio.h"

#define LCD_LEN 216
#define LCD_HIGH 118
#define WORD_LENGTH 7

typedef struct
{
    float fl;
    float fr;
    float rl;
    float rr;
} raw_data;

typedef struct
{
    float front_perc;
    float rear_perc;
    float right_perc;
    float left_perc;
} percent;

void interface_init()
{
    Lcd_Init();
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;
    setRotation(1);
}

void app_interface()
{
    raw_data data;
    data.fl = data.fr = data.rl = data.rr = 0;
    percent init_percent;
    init_percent.front_perc = init_percent.rear_perc = init_percent.left_perc = init_percent.right_perc = 0;
    LCD_ShowString(7 + 14, 0, (u8 *)("FL"), WHITE);
    LCD_ShowNum1(5 + 7, 20, data.fl, sizeof(data.fl), WHITE);

    LCD_ShowString(LCD_LEN - 12 - 7, 0, (u8 *)("FR"), WHITE);
    LCD_ShowNum1(LCD_LEN - 12 - 14 - 7, 20, data.fl, sizeof(data.fl), WHITE);

    LCD_ShowString(LCD_LEN / 2 - 12, 0, (u8 *)("FRONT"), BLUE);
    LCD_ShowNum1(LCD_LEN / 2 - 12, 20, data.fl, sizeof(data.fl), BLUE);

    LCD_ShowString(7 + 7, LCD_HIGH / 2 - 10, (u8 *)("LEFT"), BLUE);
    LCD_ShowNum1(5 + 7, LCD_HIGH / 2 - 10 + 20, data.fl, sizeof(data.fl), BLUE);

    LCD_ShowString(LCD_LEN / 2 - 12, LCD_HIGH / 2 - 10, (u8 *)("TOTAL"), YELLOW);
    LCD_ShowNum1(LCD_LEN / 2 - 12, LCD_HIGH / 2 - 10 + 20, data.fl, sizeof(data.fl), YELLOW);

    LCD_ShowString(LCD_LEN - 24 - 7, LCD_HIGH / 2 - 10, (u8 *)("RIGHT"), BLUE);
    LCD_ShowNum1(LCD_LEN - 26 - 7, LCD_HIGH / 2 - 10 + 20, data.fl, sizeof(data.fl), BLUE);

    LCD_ShowString(7 + 14, LCD_HIGH - 24, (u8 *)("RL"), WHITE);
    LCD_ShowNum1(5 + 7, LCD_HIGH - 24 + 20, data.fl, sizeof(data.fl), WHITE);

    LCD_ShowString(LCD_LEN / 2 - 7, LCD_HIGH - 24, (u8 *)("REAR"), BLUE);
    LCD_ShowNum1(LCD_LEN / 2 - 12, LCD_HIGH - 24 + 20, data.fl, sizeof(data.fl), BLUE);

    LCD_ShowString(LCD_LEN - 12 - 7, LCD_HIGH - 24, (u8 *)("RR"), WHITE);
    LCD_ShowNum1(LCD_LEN - 12 - 14 - 7, LCD_HIGH - 24 + 20, data.fl, sizeof(data.fl), WHITE);

    LCD_ShowNum1(7 + 7 + 28 + 10, LCD_HIGH / 2 - 10 + 8, init_percent.front_perc, sizeof(init_percent.front_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, LCD_HIGH / 2 - 10 + 8, init_percent.rear_perc, sizeof(init_percent.rear_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, 0 + 8, init_percent.left_perc, sizeof(init_percent.left_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, LCD_HIGH - 24 + 8, init_percent.right_perc, sizeof(init_percent.right_perc), RED);
}
