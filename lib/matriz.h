#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdint.h>
#include "hardware/pio.h"
#include "pico/stdlib.h" 

#define matriz_led_pins 25

typedef struct pixeis {
    uint8_t R, G, B;
}pixeis;



void matriz_init(uint pin); //inicialização da matriz de led.
void setled(const uint index, const uint8_t r, const uint8_t g, const uint8_t b); //configuração para permitir o uso da função display.
void matriz(uint8_t r, uint8_t g, uint8_t b);
void display(); //esta é a função responsável por permitir ditar qual led vai acender.


#endif