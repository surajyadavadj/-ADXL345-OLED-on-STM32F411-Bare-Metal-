#include "stm32f4xx.h"
#include "uart.h"

void uart2_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* PA2 = TX, PA3 = RX */
    GPIOA->MODER |=  0xA0;   // Set PA2, PA3 to AF mode
    GPIOA->AFR[0] |= (7 << 8 )| (7 << 12);

    USART2->BRR = 16000000 / 115200;   // 115200 @16MHz
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;
}

void uart_print(const char *s)
{
    while (*s)
    {
        while (!(USART2->SR & USART_SR_TXE));
        USART2->DR = *s++;
    }
}
