#include "i2c.h"

void init_i2c0(void){
    i2c_init(i2c_port0, 400 * 1000);
    gpio_set_function(i2c_SDA0, GPIO_FUNC_I2C);
    gpio_set_function(i2c_SCL0, GPIO_FUNC_I2C);
    gpio_pull_up(i2c_SDA0);
    gpio_pull_up(i2c_SCL0);        
}

void init_i2c1(void){
    i2c_init(i2c_port1, 400 * 1000);
    gpio_set_function(i2c_SDA1, GPIO_FUNC_I2C);
    gpio_set_function(i2c_SCL1, GPIO_FUNC_I2C);
    gpio_pull_up(i2c_SDA1);
    gpio_pull_up(i2c_SCL1);        
}