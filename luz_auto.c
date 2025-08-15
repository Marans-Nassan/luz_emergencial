#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "bh1750_light_sensor.h"
#include "matriz.h"
#include "i2c.h"
 
#define matriz_led 7
#define endereco 0x3c

uint32_t luz = 0;
char str_luz [16];
ssd1306_t ssd;

void display_core(void);
void oledinit(void);

int main(){
    set_sys_clock_khz(48000, true);
    stdio_init_all();
    init_i2c0();
    multicore_launch_core1(display_core);
    matriz_init(matriz_led);
    bh1750_power_on(i2c_port0);
    sleep_ms(1000);

    while (true) {
        luz = bh1750_read_measurement(i2c_port0);
        snprintf(str_luz, sizeof(str_luz), "Luz = %d", luz);
        printf("Luz atual: %d\n", luz);
        (luz < 20) ? matriz(255, 255, 255) : matriz(0, 0, 0);
        sleep_ms(200);
    }
}

void display_core(void){
    init_i2c1();
    oledinit();
    while(true){
        ssd1306_draw_string (&ssd, str_luz, 0, 25);
        ssd1306_send_data(&ssd);
        sleep_ms(50);
    }
}

void oledinit(void){
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, i2c_port1);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}