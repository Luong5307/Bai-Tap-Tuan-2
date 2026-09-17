#include <stdint.h>

#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800
#define TIM2_BASE       0x40000000

#define RCC_APB2ENR     *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_APB1ENR     *(volatile uint32_t *)(RCC_BASE + 0x1C)

#define GPIOA_CRL       *(volatile uint32_t *)(GPIOA_BASE + 0x00)

#define TIM2_CR1        *(volatile uint32_t *)(TIM2_BASE + 0x00)
#define TIM2_CCMR1      *(volatile uint32_t *)(TIM2_BASE + 0x18)
#define TIM2_CCMR2      *(volatile uint32_t *)(TIM2_BASE + 0x1C)
#define TIM2_CCER       *(volatile uint32_t *)(TIM2_BASE + 0x20)
#define TIM2_PSC        *(volatile uint32_t *)(TIM2_BASE + 0x28)
#define TIM2_ARR        *(volatile uint32_t *)(TIM2_BASE + 0x2C)
#define TIM2_CCR1       *(volatile uint32_t *)(TIM2_BASE + 0x34)
#define TIM2_CCR2       *(volatile uint32_t *)(TIM2_BASE + 0x38)
#define TIM2_CCR3       *(volatile uint32_t *)(TIM2_BASE + 0x3C)
#define TIM2_CCR4       *(volatile uint32_t *)(TIM2_BASE + 0x40)

__attribute__((used)) void SystemInit(void) {}

void PWM_Init(void) {
    RCC_APB2ENR |= (1 << 2);
    RCC_APB1ENR |= (1 << 0);

    GPIOA_CRL &= ~(0xFFFFFFFF);
    GPIOA_CRL |= (0x0B << 0) | (0x0B << 4) | (0x0B << 8) | (0x0B << 12);

    TIM2_PSC = 7;
    TIM2_ARR = 999;

    TIM2_CCMR1 |= (0x68 << 0) | (0x68 << 8);
    TIM2_CCMR2 |= (0x68 << 0) | (0x68 << 8);

    TIM2_CCR1 = 100;
    TIM2_CCR2 = 300;
    TIM2_CCR3 = 500;
    TIM2_CCR4 = 700;

    TIM2_CCER |= (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12);

    TIM2_CR1 |= (1 << 0);
}

int main(void) {
    PWM_Init();

    while (1) {
    }
}
