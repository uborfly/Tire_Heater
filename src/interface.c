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
    float front;
    float rear;
    float left;
    float right;
} calced_data;

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

void set_raw_data(raw_data data)
{
    LCD_ShowString(7 + 14, 0, (u8 *)("FR"), WHITE);
    LCD_ShowNum1(5 + 7, 20, data.fr, sizeof(data.fr), WHITE);

    LCD_ShowString(7 + 14, LCD_HIGH - 24, (u8 *)("FL"), WHITE);
    LCD_ShowNum1(5 + 7, LCD_HIGH - 24 + 20, data.fl, sizeof(data.fl), WHITE);

    LCD_ShowString(LCD_LEN - 12 - 7, 0, (u8 *)("RR"), WHITE);
    LCD_ShowNum1(LCD_LEN - 12 - 14 - 7, 20, data.rr, sizeof(data.rr), WHITE);

    LCD_ShowString(LCD_LEN - 12 - 7, LCD_HIGH - 24, (u8 *)("RL"), WHITE);
    LCD_ShowNum1(LCD_LEN - 12 - 14 - 7, LCD_HIGH - 24 + 20, data.rl, sizeof(data.rl), WHITE);
}

void set_calced_data(calced_data data)
{
    LCD_ShowString(LCD_LEN / 2 - 12, 0, (u8 *)("LEFT"), BLUE);
    LCD_ShowNum1(LCD_LEN / 2 - 12, 20, data.left, sizeof(data.left), BLUE);

    LCD_ShowString(7 + 7, LCD_HIGH / 2 - 10, (u8 *)("FRONT"), BLUE);
    LCD_ShowNum1(5 + 7, LCD_HIGH / 2 - 10 + 20, data.front, sizeof(data.front), BLUE);

    LCD_ShowString(LCD_LEN - 24 - 7, LCD_HIGH / 2 - 10, (u8 *)("REAR"), BLUE);
    LCD_ShowNum1(LCD_LEN - 26 - 7, LCD_HIGH / 2 - 10 + 20, data.rear, sizeof(data.rear), BLUE);

    LCD_ShowString(LCD_LEN / 2 - 7, LCD_HIGH - 24, (u8 *)("RIGHT"), BLUE);
    LCD_ShowNum1(LCD_LEN / 2 - 12, LCD_HIGH - 24 + 20, data.right, sizeof(data.right), BLUE);
}

void set_percent_data(percent data)
{
    LCD_ShowNum1(7 + 7 + 28 + 10, LCD_HIGH / 2 - 10 + 8, data.front_perc, sizeof(data.front_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, LCD_HIGH / 2 - 10 + 8, data.rear_perc, sizeof(data.rear_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, 0 + 8, data.left_perc, sizeof(data.left_perc), RED);
    LCD_ShowNum1(LCD_LEN / 2 - 12 + 35 + 10, LCD_HIGH - 24 + 8, data.right_perc, sizeof(data.right_perc), RED);
}
/*
    FR      LEFT    RR
    FRONT   TOTAL   REAR
    FL      RIGHT   RL
*/
void app_interface()
{
    raw_data data;
    data.fl = data.fr = data.rl = data.rr = 0;
    calced_data calced;
    calced.front = calced.rear = calced.left = calced.right = 0;
    percent init_percent;
    init_percent.front_perc = init_percent.rear_perc = init_percent.left_perc = init_percent.right_perc = 0;

    set_raw_data(data);
    set_calced_data(calced);
    set_percent_data(init_percent);

    LCD_ShowString(LCD_LEN / 2 - 12, LCD_HIGH / 2 - 10, (u8 *)("TOTAL"), YELLOW);
    LCD_ShowNum1(LCD_LEN / 2 - 12, LCD_HIGH / 2 - 10 + 20, data.fl, sizeof(data.fl), YELLOW);
}
