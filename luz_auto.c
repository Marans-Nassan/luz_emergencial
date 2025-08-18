#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"
#include "bh1750_light_sensor.h"
#include "matriz.h"
#include "i2c.h"
#include "string.h"

#define matriz_led 7
#define endereco 0x3c

uint32_t luz = 0;
bool escuroDetectado = false;
unsigned long tempoPrimeiraDeteccao = 0;
char str_luz [16];
ssd1306_t ssd;

bool luz_alta = false;

void display_core(void);
void oledinit(void);
uint8_t xcenter_pos(char* text);

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
        snprintf(str_luz, sizeof(str_luz), "Nivel = %d", luz);
        printf("Luz atual: %d\n", luz);
        
        if (luz < 20) {
            if (!escuroDetectado) {
                escuroDetectado = true;
                tempoPrimeiraDeteccao = to_ms_since_boot(get_absolute_time());
                printf("Escuro detectado!\n");
            } else if (escuroDetectado && (to_ms_since_boot(get_absolute_time()) - tempoPrimeiraDeteccao) > 3000) {
                matriz(1, 1, 1);
                // buzzer
            }
        } else {
            escuroDetectado = false;
            matriz(0, 0, 0);
        }
        
        sleep_ms(200);
    }
}

void display_core(void){
    init_i2c1();
    oledinit();
    while(true){
        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "Luz", xcenter_pos("Luz"), 2);
        ssd1306_draw_string(&ssd, "Emergencial", xcenter_pos("Emergencial"), 10);
        ssd1306_hline(&ssd, 0, WIDTH-1,  20, true);
        ssd1306_draw_string(&ssd, str_luz, xcenter_pos(str_luz), 28);
        escuroDetectado ? ssd1306_draw_string(&ssd, "Escuro", xcenter_pos("Escuro"), 40) : ssd1306_draw_string(&ssd, "Claro", xcenter_pos("Claro"), 40);
        ssd1306_draw_string(&ssd, "Modo manual:OFF", xcenter_pos("Modo manual:OFF"), 54);
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

uint8_t xcenter_pos(char* text) {
    return (WIDTH - 8 * strlen(text)) / 2; // Calcula a posição centralizada
}