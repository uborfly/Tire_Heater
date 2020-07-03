#include "hx711.h"
#include "gd32vf103_gpio.h"

#define HX711_DATA PEin(0)
#define HX711_SCK PEout(1)

void HX711_init(void)
{

    gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);

    gpio_bit_set(GPIOB, GPIO_PIN_10); //PE1 SCK

    gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_13); //PE0 in
}

uint8_t HX711_GetValue(uint32_t *value)
{
    int retry = 0;
    uint32_t ret = 0;

    HX711_SCK = 0;
    while (retry < 200)
    {
        delay_us(1);
        if (HX711_DATA == 0)
            break;
        else
            retry++;
    }
    if (retry == 200)
        return 1;

    for (int i = 0; i < 24; i++)
    {
        HX711_SCK = 1;
        delay_us(1);
        ret = ret << 1;
        HX711_SCK = 0;
        ret |= HX711_DATA;
        delay_us(1);
    }

    HX711_SCK = 1;
    delay_us(1);
    *value = ret ^ 0x800000;
    //*value = ret;
    HX711_SCK = 0;
    delay_us(1);

    return 0;
}
