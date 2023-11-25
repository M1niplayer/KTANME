#include <pic32mx.h>
#include <stdint.h>
#include "./i2c.h"
/* It's technically an adress, but it's technically also a control code
* the entire byte will look like this:
* 1010 000X 
*
* First four bits are the control bits (24LC256 is 1010)
* Next three bit are the chip select bits (000 in this case)
* where X is the R/W bit (0 for write, 1 for read)
*/
#define EEPROM_ADDRESS_BYTE 0x50 

//void write(uint16_t address, uint8_t[64] data){
//    //the same thing except 64 times
//};
void write(uint16_t address, uint8_t data){
    //set up i2c bus with address
    
    //could do something with interrputs
    //I2CxMIF,
    //probably have to handle bus collisions
    //I2CxBIF
    do{
        i2c_start();
        i2c_send(EEPROM_ADDRESS_BYTE << 1); 
    } while (!i2c_ackstat());
    
    i2c_ackstat();
    
    //make sure I2C bus is not being used
    //code
    
}
//maybe one for currentread

//this is random read, i.e you can access any legal memory loc you want
uint8_t readbyte(uint16_t address){
    //set up i2c bus with address
    uint8_t temp;
    read_EEPROM_adr(address);
    //start receiving
    temp = i2c_recv();
    i2c_set_nack();
    i2c_stop();
    return temp;
}

void write_EEPROM_adr(uint16_t address){
    do{
        i2c_start();
        i2c_send(EEPROM_ADDRESS_BYTE << 1); //note, random reads require write byte
    } while (!i2c_ackstat()); //might or might not work
    //write address
    i2c_send(address >> 8);
    i2c_set_ack();
    i2c_send(address & 0xFF);
    i2c_set_ack();
}

void read_EEPROM_adr(uint16_t address){
    write_EEPROM_adr(address);
    //generate start and terminate write operation.
    do{
        i2c_start();
        i2c_send(EEPROM_ADDRESS_BYTE << 1 | 1); //note, random reads require write byte
    } while (!i2c_ackstat());
}