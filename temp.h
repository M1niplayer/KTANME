#pragma once

#include <pic32mx.h>
#include <stdint.h>
#include "i2c.h"

#define TEMP_CLIENT_ADDR 0x48

enum TEMP_ADDRESS {
    TEMP_REG_TEMP,
    TEMP_REG_CONFIG,
    TEMP_REG_THYST,
    TEMP_REG_TSET,
};

int read_temp(void);
void set_temp_config(uint8_t config);
void set_temp_limits(int low, int high); //i