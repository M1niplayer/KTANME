/* most of this will be yoinked from the 
* temp i2c example code at IS1200 example projects
*
*/
#pragma once

#include <pic32mx.h>
#include <stdint.h>

//On POR, at I2CxCON, only SCLREL is set to 1, everything else to 0


void i2c_idle();
bool i2c_send();
uint8_t i2c_recieve(uint8_t data);
void i2c_ack() ; 
void i2c_nack();
void i2c_start();
void i2c_restart();
void i2c_stop();
