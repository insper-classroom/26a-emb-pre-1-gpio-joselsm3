#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

static const uint FIRST_GPIO = 2u;
static const uint BTN_PIN = 28u;

// Converte 0-9 para o padrão (a..g) a ser enviado aos GPIOs
static const uint8_t bits[10] = {
    0x3f,  // 0
    0x06,  // 1
    0x5b,  // 2
    0x4f,  // 3
    0x66,  // 4
    0x6d,  // 5
    0x7d,  // 6
    0x07,  // 7
    0x7f,  // 8
    0x67   // 9
};

static int cnt = 2;           // mantém o comportamento: inicia exibindo 2
static bool last_btn = true;  // botão puxado pra cima: true = solto

static void seven_seg_init(void) {
    for (uint gpio = FIRST_GPIO; gpio < (FIRST_GPIO + 7u); gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
        gpio_put(gpio, 0); // estado conhecido ao inicializar
    }
}

static void seven_seg_display(int digit) {
    // Mantém o comportamento esperado: só exibe 0..9
    if (digit < 0 || digit > 9) {
        return;
    }

    const uint8_t value = bits[digit];
    for (uint i = 0; i < 7u; i++) {
        const uint gpio = FIRST_GPIO + i;
        const bool bit = ((value >> i) & 1u) != 0u;
        gpio_put(gpio, bit);
    }
}

int main(void) {
    stdio_init_all();

    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    seven_seg_init();
    seven_seg_display(cnt);

    while (true) {
        const bool btn = gpio_get(BTN_PIN) != 0u;

        // borda de descida: solto (1) -> pressionado (0)
        if (last_btn && !btn) {
            cnt++;
            if (cnt > 9) {
                cnt = 0;
            }
            seven_seg_display(cnt);
            printf("cnt: %d\r\n", cnt);
        }

        last_btn = btn;
        sleep_ms(10); // intervalo do polling
    }
}