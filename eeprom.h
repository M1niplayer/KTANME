#pragma once

#include <pic32mx.h>
#include <stdint.h>
/* It's technically an adress, but it's technically also a control code
* the entire byte will look like this:
* 1010 000X 
*
* First four bits are the control bits (24LC256 is 1010)
* Next three bit are the chip select bits (000 in this case)
* where X is the R/W bit (0 for write, 1 for read)
*/
#define EEPROM_CONTROL_BYTE 0x50 
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
* Send start condition 
* Send control byte with R/W bit set to 0
* Send ACK
* send 8 MSB of address. Note that the highest bit doesn't actually matter
* Send ACK
* Send 8 LSB of address
* Send ACK
* Send data
* Send ACK
* Continue sending data up to 64 bytes. Send ACK after each byte.
* Send stop condition and probably a nack (in reverse order)
*/

/* Write your sick ass data at an 16 bit address
* Args: 
* uint16_t 'address'. Address in EEPROM. In total 32kB spots. Make sure it's 
* page aligned because otherwise you'll wrap around in the page and
* potentially overwrite data at LSB of address.
*
* uint8_t[64] data. Data to be stored. Data sits in pages in EEPROM. 
*/
void write(uint16_t address);