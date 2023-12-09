#include <pic32mx.h>
#include <stdint.h>
#include "i2c.h"
#include "eeprom.h"
/* It's technically an adress, but it's technically also a control code
* the entire byte will look like this:
* 1010 000X 
*
* First four bits are the control bits (24LC256 is 1010)
* Next three bit are the chip select bits (since we only have one 24XX256, this is 000)
* where X is the R/W bit (0 for write, 1 for read)
*/
#define EEPROM_CLIENT_ADDRESS 0x50 

//void write(uint16_t address, uint8_t[64] data){
//    //the same thing except 64 times
//};
void write_single_byte(uint16_t address, uint8_t data){
    //set up i2c bus with address
    _write_EEPROM_adr(address);
    //could do something with interrputs
    //I2CxMIF, master interupt
    //probably have to handle bus collisions
    //I2CxBIF
    i2c_send(data);
    i2c_recv_ack();
    i2c_stop();
}
//maybe one for currentread

//this is random read, i.e you can access any legal memory loc you want
uint8_t read_single_byte(uint16_t address){
    uint8_t temp;
    //set up i2c bus with address so that we can receive
    _recv_EEPROM_adr(address);

    //start receiving
    temp = i2c_recv();
    i2c_set_nack();
    i2c_stop();
    return temp;
}
/*doesn't necessarily have to be 64 size array.
take caution in making sure that you don't overwrite
data when you do page unaligned writes */
void write_page(uint16_t address, uint8_t data[4]){
    //set up i2c bus with address
    _write_EEPROM_adr(address);
    
    int i = 0;
    for (i = 0; i < 64; i++){
        i2c_send(data[i]);
        i2c_recv_ack();
    }
    i2c_stop();
}
//must be 64 bit size array
void read_page(uint16_t address, uint8_t* temp){
    //set up i2c bus with address so that we can receive
    _recv_EEPROM_adr(address);

    //start receiving
    int i = 0;
    for (i = 0; i < I2C_PAGEWRITE_CAP - 1; i++){
        temp[i] = i2c_recv();
        i2c_set_ack();
    }
    temp[63] = i2c_recv();
    i2c_set_nack(); //important
    i2c_stop();
}

void _write_EEPROM_adr(uint16_t address){
    do{
        i2c_start();
         //note, random reads require write byte
    } while (!i2c_send(EEPROM_CLIENT_ADDRESS << 1)); //might or might not work
    //write address
    i2c_send(address >> 8);
    i2c_recv_ack();
    i2c_send(address & 0xFF);
    i2c_recv_ack();
}

void _recv_EEPROM_adr(uint16_t address){
    _write_EEPROM_adr(address);
    //generate start and terminate write operation.
    i2c_start();
    i2c_send(EEPROM_CLIENT_ADDRESS << 1 | 1);
    i2c_recv_ack(); //might or might not work
}
