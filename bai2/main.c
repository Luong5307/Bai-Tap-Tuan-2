#include <stdint.h>

/* Địa chỉ thanh ghi RCC, GPIOA và SysTick */
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800
#define SYSTICK_BASE    0xE000E010

#define RCC_APB2ENR     *(volatile uint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRL       *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_ODR       *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

#define SYST_CSR        *(volatile uint32_t *)(SYSTICK_BASE + 0x00)
#define SYST_RVR        *(volatile uint32_t *)(SYSTICK_BASE + 0x04)
#define SYST_CVR        *(volatile uint32_t *)(SYSTICK_BASE + 0x08)

/* Khai báo chân LED nối vào PA0, PA1, PA2 */
#define LED1_PIN        0 // Tần số 0.1 Hz (Chu kỳ 10s -> Đảo trạng thái mỗi 5s = 5000ms)
#define LED2_PIN        1 // Tần số 1 Hz   (Chu kỳ 1s  -> Đảo trạng thái mỗi 0.5s = 500ms)
#define LED3_PIN        2 // Tần số 10 Hz  (Chu kỳ 0.1s -> Đảo trạng thái mỗi 0.05s = 50ms)

/* Biến đếm thời gian trong ngắt (đơn vị: ms) */
volatile uint32_t ms_ticks = 0;
volatile uint32_t t_led1 = 0;
volatile uint32_t t_led2 = 0;
volatile uint32_t t_led3 = 0;

__attribute__((used)) void SystemInit(void) {}

/* Cấu hình SysTick tạo ngắt mỗi 1ms (1000Hz) */
void SysTick_Init(void) {
    // Với thạch anh/Clock mặc định HSI 8MHz -> 1ms tương ứng 8000 chu kỳ
    SYST_RVR = 8000 - 1; 
    SYST_CVR = 0; // Xóa giá trị đếm hiện tại
    // Enable SysTick, Enable Interrupt, Chọn nguồn Clock hệ thống (CLKSOURCE = 1)
    SYST_CSR = (1 << 0) | (1 << 1) | (1 << 2);
}

/* Trình xử lý ngắt SysTick (được gọi tự động mỗi 1ms) */
void SysTick_Handler(void) {
    ms_ticks++;
    t_led1++;
    t_led2++;
    t_led3++;

    // LED 3: 10Hz -> Chu kỳ 100ms (Đảo trạng thái mỗi 50ms)
    if (t_led3 >= 50) {
        GPIOA_ODR ^= (1 << LED3_PIN);
        t_led3 = 0;
    }

    // LED 2: 1Hz -> Chu kỳ 1000ms (Đảo trạng thái mỗi 500ms)
    if (t_led2 >= 500) {
        GPIOA_ODR ^= (1 << LED2_PIN);
        t_led2 = 0;
    }

    // LED 1: 0.1Hz -> Chu kỳ 10000ms (Đảo trạng thái mỗi 5000ms)
    if (t_led1 >= 5000) {
        GPIOA_ODR ^= (1 << LED1_PIN);
        t_led1 = 0;
    }
}

void GPIO_Init(void) {
    // 1. Bật Clock cho GPIOA
    RCC_APB2ENR |= (1 << 2);

    // 2. Cấu hình PA0, PA1, PA2 là Output Push-Pull 2MHz (0x02)
    GPIOA_CRL &= ~(0xFFF); // Xóa cấu hình cũ của PA0, PA1, PA2
    GPIOA_CRL |= (0x02 << 0) | (0x02 << 4) | (0x02 << 8);
}

int main(void) {
    GPIO_Init();
    SysTick_Init();

    while (1) {
        // Vòng lặp trống, mọi tác vụ đảo trạng thái LED được thực hiện trong ngắt SysTick
    }
}
