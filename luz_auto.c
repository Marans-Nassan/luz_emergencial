#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "bh1750_light_sensor.h"
#include "matriz.h"

#define matriz_led 7


int main(){
    stdio_init_all();
    matriz_init(7);

    while (true) {
        printf("Hello, world!\n");
        matriz(255, 255, 255);
        sleep_ms(1000);
    }
}
