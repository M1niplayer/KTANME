#pragma once

#include <pic32mx.h>
#include <stdint.h>
#include "i2c.h"
/* It's technically an adress, but it's technically also a control code
* the entire byte will look like this:
* 1010 000X 
*
* First four bits are the control bits (24LC256 is 1010)
* Next three bit are the chip select bits (000 in this case)
* where X is the R/W bit (0 for write, 1 for read)
*/
#define EEPROM_ADDRESS_BYTE 0x50 
/* If cap was less than 64, say 16, you would have to increment the address by 16
* each time. Issue is, the entire page endures a write regardless if the cap is 64
* or 16 bits.
*
* Also note, if you write more than 64 bytes, it will wrap around to the
* beginning of the page and overwrite the data there.
* Also note, unaligned page writes will also wrap around.
*/
#define I2C_PAGEWRITE_CAP 64

/*anatomy of a write
* Send start condition (SEN = 1)
* Send control byte with R/W bit set to 0
* Send ACK (ACKDT = 0, ACKEN = 1)
* send 8 MSB of address. Note that the highest bit doesn't actually matter
* Send ACK
* Send 8 LSB of address
* Send ACK
* Send data
* Send ACK
* Continue sending data up to 64 bytes. Send ACK after each byte.
* Either send a nack (ACKDT = 1, ACKEN = 1) or a restart (RSEN = 1)
* bla bla
* Send stop condition (PEN = 1) clears other bits automatically (I2C slave is disabled)
*/

/* Write your sick ass data at an 16 bit address
* Args: 
* uint16_t 'address'. Address in EEPROM. In total 32kB spots. Make sure it's 
* page aligned because otherwise you'll wrap around in the page and
* potentially overwrite data at LSB of address.
*
* uint8_t[64] data. Data to be stored. Data sits in pages in EEPROM. 
*/
void write_single_byte(int address, uint8_t data);
uint8_t read_single_byte(int address);

//this is set automatically via readbyte and readmany
void write_EEPROM_adr(int address);
void recv_EEPROM_adr(int address);