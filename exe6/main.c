#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

int FIRST_GPIO = 2;
const int BTN_PIN_G = 28;

int BUTTON_GPIO;
int cnt;
int last_btn; // Button not pressed (pulled up)

// This array converts a number 0-9 to a bit pattern to send to the GPIOs
int bits[10] = {
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

void seven_seg_init() {
    for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }
}

void seven_seg_display() {
    int value = bits[cnt];
    for (int i = 0; i < 7; i++) {
        int gpio = FIRST_GPIO + i;
        int bit = (value >> i) & 1;
        gpio_put(gpio, bit);
    }
}

int main() {
    stdio_init_all();
    int aux = 0;

    BUTTON_GPIO = FIRST_GPIO + 7;

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    seven_seg_init();
    seven_seg_display(2);

    while (true) {
        int btn = gpio_get(BTN_PIN_G);
        if (last_btn && !btn) { // Detect falling edge (press)
            if (++cnt > 9) {
                cnt = 0;
            }
            seven_seg_display();
            printf("cnt: %l\n", cnt);
        }
        last_btn = btn;
        sleep_ms(10); // Polling interval
    }
}
