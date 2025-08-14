#ifndef I2C_H
#define I2C_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define i2c_port0 i2c0
#define i2c_SDA0 0
#define i2c_SCL0 1
#define i2c_port1 i2c1
#define i2c_SDA1 14
#define i2c_SCL1 15


void init_i2c0(void);
void init_i2c1(void);

#endif