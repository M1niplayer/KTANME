#include "temp.h"

int read_temp(){
    int temp = 0;
    do { //write register pointer
        i2c_start();
    } while(i2c_send(TEMP_CLIENT_ADDR << 1));
    i2c_send(TEMP_REG_TEMP); 

    do { //read temperature
        i2c_start();
    } while(i2c_send(TEMP_CLIENT_ADDR << 1) | 1);

    temp = i2c_recv() << 8; 
    i2c_set_ack();
    temp = temp | i2c_recv(); //LSB. Can include useless info. 
    i2c_set_nack();
    i2c_stop();
    return temp;
}
/* Set_config
MSB is One-Shot mode (something to do with shutdown)

Bit 6-5 is resolution. 00 is 9 bit resolution (delta = 0.5c) and 11 is 12 bit resolution (delta = 0.0625c)
(note that higher resolution makes for longer polling time. 9 bit is 30ms and 12 bit is 240ms.)

Bit 4-3 is Fault Queue Size. goes from 1, 2, 4, 6. Default is 1.

Bit 2 is Alert Polarity Bit. If 0, then ALERT will be logic low. 

Bit 1 is COMP/INT (comparator, interrupt) mode. 0 is comparator.

Bit 0 is Shutdown. 0 is no shutdown

just send 00100000 lmao*/
void set_config(uint8_t config){
    do { //write register pointer
        i2c_start();
    } while(i2c_send(TEMP_CLIENT_ADDR << 1));
    i2c_send(TEMP_REG_CONFIG); 
    i2c_recv_ack();
    
    i2c_send(config);
    i2c_recv_ack();
    i2c_stop();
}

/* In celsius. Each register is 9 bits signed size. */
void set_limits(int low, int high){
    do { //write register pointer
        i2c_start();
    } while(i2c_send(TEMP_CLIENT_ADDR << 1));
    i2c_send(TEMP_REG_THYST); 
    i2c_recv_ack();
    i2c_send(low);
    i2c_recv_ack();
    i2c_stop();

    do { //write register pointer
        i2c_start();
    } while(i2c_send(TEMP_CLIENT_ADDR << 1));
    i2c_send(TEMP_REG_TSET);
    i2c_recv_ack();
    i2c_send(high);
    i2c_recv_ack();
    i2c_stop();
}