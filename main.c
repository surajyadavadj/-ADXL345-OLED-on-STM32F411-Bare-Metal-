#include "stm32f4xx.h"
#include "uart.h"
#include "i2c.h"
#include "adxl345.h"
#include "oled.h"
volatile uint8_t activity_flag = 0;

// EXTI0 - PA0 (ADXL345 INT1) 
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0)
    {
        activity_flag = 1;
        EXTI->PR = EXTI_PR_PR0;
    }
}

int main(void)
{
    uart2_init();
    i2c1_init();
    i2c1_init();
    oled_init();
    oled_clear();

    oled_set_cursor(0, 12);
    oled_write_string("HELLO ADXL");


    uart_print("ADXL345 Activity > 2.0g\r\n");
    adxl345_init_activity();

   // EXTI config PA0 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    GPIOA->MODER |= 0x00;
    GPIOA->MODER |= 0x0400;
    SYSCFG->EXTICR[0] = 0;
    EXTI->IMR |= EXTI_IMR_IM0;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    NVIC_EnableIRQ(EXTI0_IRQn);

    while (1)
    {
        if (activity_flag)
        {
            activity_flag = 0;

            if (adxl345_read_int_source() & 0x10)
            {
                oled_set_cursor(4, 20);
                oled_write_string("DETECTED 2 G");

                uart_print(" ACTIVITY > 2.0g DETECTED\r\n");
                GPIOA ->ODR |= 0x20;
            }
            else{
                GPIOA ->ODR &= 0x00;
                oled_set_cursor(4, 20);
                oled_write_string("NO,DETECT");

                uart_print(" NOT ACTIVITY > 2.0g DETECTED\r\n");
                
            }
                    
        }

    }
}
