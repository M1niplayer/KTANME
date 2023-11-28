/*
* HI
* most of this will be yoinked from the 
* temp i2c example code at IS1200 example projects
*
*/

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

int32_t i2c_test(){
	return 98765432;
}
void i2c_idle() {
    //I2C1CON has SEN, RSEN, PEN, RCEN, ACKEN
    //i.e start enable, reset enable, stop enable, receive enable, acknoledge enable
    //related to master logic (you receive from slave)
    //I2C1STAT has TRSTAT - i.e transmit status
	while(I2C1CON & 0x1F || I2C1STAT & (1 << 14)); 
}

/* Send one byte on I2C bus, return ack/nack status of transaction */
bool i2c_send(uint8_t data) {
	i2c_idle();
	I2C1TRN = data;
	i2c_idle();
	return !(I2C1STAT & (1 << 15)); //ACKSTAT
}

//true if received ack, false if not received ack
//i.e, 1 if not received ack, 0 if received. 
//bool i2c_ackstat() {
//    return (!I2C1STAT & (1 << 15)); //ACKSTAT
//}
/* Receive one byte from I2C bus */
uint8_t i2c_recv() {
	i2c_idle();
	I2C1CONSET = 1 << 3; //RCEN = 1
	i2c_idle();
	I2C1STATCLR = 1 << 6; //I2COV = 0. i.e don't clear I2CxRSR
	return I2C1RCV;
}

//note that you have to send an ack after each byte
//or well, this is done automatically

/* Send acknowledge conditon on the bus */
void i2c_set_ack() {
	i2c_idle();
	I2C1CONCLR = 1 << 5; //ACKDT = 0
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

/* Send not-acknowledge conditon on the bus */
void i2c_set_nack() {
	i2c_idle();
	I2C1CONSET = 1 << 5; //ACKDT = 1
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

void i2c_recv_ack() {
	i2c_idle();
	while(!I2C1STAT & (1 << 15)); //wait until ack has been sent
}
/* Send start conditon on the bus */
void i2c_start() {
	i2c_idle();
	I2C1CONSET = 1 << 0; //SEN
	i2c_idle();
}

/* Send restart conditon on the bus */
void i2c_restart() {
	i2c_idle();
	I2C1CONSET = 1 << 1; //RSEN
	i2c_idle();
}

/* Send stop conditon on the bus */
void i2c_stop() {
	i2c_idle();
	I2C1CONSET = 1 << 2; //PEN
	i2c_idle();
}