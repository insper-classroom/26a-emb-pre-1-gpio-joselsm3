#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN1 = 28;
const int BTN2 = 26;
const int LED_R = 4;
const int LED_G = 6;

int main() {
    stdio_init_all();

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_init(BTN1);
    gpio_set_dir(BTN1, GPIO_IN);
    gpio_pull_up(BTN1);

    gpio_init(BTN2);
    gpio_set_dir(BTN2, GPIO_IN);
    gpio_pull_up(BTN2);

    while (true) {

        if (gpio_get(BTN1) == 0) {
            gpio_put(LED_R, !gpio_get(LED_R));
            sleep_ms(200);
        } 

        if (gpio_get(BTN2) == 0) {
            gpio_put(LED_G, !gpio_get(LED_G));
            sleep_ms(200);
        }

        sleep_ms(50);
    }
}