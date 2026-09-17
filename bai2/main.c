#include <stdint.h>

#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800
#define SYSTICK_BASE    0xE000E010

#define RCC_APB2ENR     *(volatile uint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRL       *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR       *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define SYST_CSR        *(volatile uint32_t *)(SYSTICK_BASE + 0x00)
#define SYST_RVR        *(volatile uint32_t *)(SYSTICK_BASE + 0x04)
#define SYST_CVR        *(volatile uint32_t *)(SYSTICK_BASE + 0x08)

#define LED1_PIN        0
#define LED2_PIN        1
#define LED3_PIN        2

volatile uint32_t ms_ticks = 0;
volatile uint32_t t_led1 = 0;
volatile uint32_t t_led2 = 0;
volatile uint32_t t_led3 = 0;

__attribute__((used)) void SystemInit(void) {}

void SysTick_Init(void) {
    SYST_RVR = 8000 - 1;
    SYST_CVR = 0;
    SYST_CSR = (1 << 0) | (1 << 1) | (1 << 2);
}

void SysTick_Handler(void) {
    ms_ticks++;
    t_led1++;
    t_led2++;
    t_led3++;

    if (t_led3 >= 50) {
        GPIOA_ODR ^= (1 << LED3_PIN);
        t_led3 = 0;
    }

    if (t_led2 >= 500) {
        GPIOA_ODR ^= (1 << LED2_PIN);
        t_led2 = 0;
    }

    if (t_led1 >= 5000) {
        GPIOA_ODR ^= (1 << LED1_PIN);
        t_led1 = 0;
    }
}

void GPIO_Init(void) {
    RCC_APB2ENR |= (1 << 2);

    GPIOA_CRL &= ~(0xFFF);
    GPIOA_CRL |= (0x02 << 0) | (0x02 << 4) | (0x02 << 8);
}

int main(void) {
    GPIO_Init();
    SysTick_Init();

    while (1) {
    }
}
