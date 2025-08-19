    #include "hardware/pwm.h"
    #include "hardware/gpio.h"
    #include <stdio.h>  
    #include "pico/stdlib.h"
    #define BUZZER_PIN 10

    void controlaBuzzer(uint gpio, uint level){
    const uint16_t period = 20000; //  20ms = 20000 ticks
    const float DIVIDER_PWM = 125.0; //Divisor de clock
    uint slice_num;

    gpio_set_function(gpio, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(gpio);
  
    pwm_set_clkdiv(slice_num, 125.0); // 125 MHz / 125 = 1 MHz
    pwm_set_wrap(slice_num, 250);     // 1 MHz / 250 = 4 kHz (frequência audível)
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0); //Inicia o BUZZ desligado
    pwm_set_enabled(slice_num, true);// Inicia o PWM
    uint slice = pwm_gpio_to_slice_num(gpio);
    uint chan = pwm_gpio_to_channel(gpio);
    
    pwm_set_chan_level(slice, chan, level);
    sleep_ms(500);
    pwm_set_chan_level(slice, chan, 0);
    }