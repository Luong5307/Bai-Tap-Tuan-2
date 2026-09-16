#include <stdint.h>

/* Địa chỉ các thanh ghi RCC, GPIOA, TIM2 */
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
    // 1. Bật Clock cho GPIOA (bit 2) và TIM2 (bit 0)
    RCC_APB2ENR |= (1 << 2);
    RCC_APB1ENR |= (1 << 0);

    // 2. Cấu hình PA0, PA1, PA2, PA3 là Alternate Function Push-Pull 50MHz (Mã 0x0B)
    GPIOA_CRL &= ~(0xFFFFFFFF);
    GPIOA_CRL |= (0x0B << 0) | (0x0B << 4) | (0x0B << 8) | (0x0B << 12);

    // 3. Cấu hình Tần số Timer 2 = 1kHz
    TIM2_PSC = 7;     // Tần số Timer = 8MHz / (7 + 1) = 1MHz
    TIM2_ARR = 999;   // Chu kỳ PWM = 1000 xung (0..999) -> Tần số = 1MHz / 1000 = 1kHz

    // 4. Cấu hình chế độ PWM Mode 1 cho 4 kênh (CH1, CH2, CH3, CH4)
    // OCxM = 110 (PWM mode 1) + OCxPE = 1 (Preload enable)
    TIM2_CCMR1 |= (0x68 << 0) | (0x68 << 8);  // Kênh 1 & Kênh 2
    TIM2_CCMR2 |= (0x68 << 0) | (0x68 << 8);  // Kênh 3 & Kênh 4

    // 5. Cấu hình Duty Cycle cho 4 LED
    TIM2_CCR1 = 100;  // Duty 10%  (100/1000)
    TIM2_CCR2 = 300;  // Duty 30%  (300/1000)
    TIM2_CCR3 = 500;  // Duty 50%  (500/1000)
    TIM2_CCR4 = 700;  // Duty 70%  (700/1000)

    // 6. Cho phép xuất tín hiệu ở các chân đầu ra (CC1E, CC2E, CC3E, CC4E)
    TIM2_CCER |= (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12);

    // 7. Cho phép Timer 2 bắt đầu đếm (CEN bit)
    TIM2_CR1 |= (1 << 0);
}

int main(void) {
    PWM_Init();

    while (1) {
        // Chương trình chạy duy trì PWM ở phần cứng Timer
    }
}
