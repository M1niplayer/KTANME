#pragma once

#include <pic32mx.h>
#include <stdint.h>

#include "i2c.h"
#include "eeprom.h"

#define HIGHSCORE_SIZE 10

typedef struct {
    char name[3];
    uint8_t score;
} highscore_t;

void save_highscore(char *name, uint8_t score);
void load_highscore(highscore_t *highscores);
