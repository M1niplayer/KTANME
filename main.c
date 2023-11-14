#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"

#define METADATA 0
#define WIDTH 8
#define HEIGHT 0
#define ALPHA 31
#define IMAGE 1

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

void interrupt(void)
{
  return;
}

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void set_pos(uint8_t column, uint8_t row) {
  //command mode
  DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
  //set row
  spi_send_recv(0xb0 | (row & 0xF));
  //set column
  spi_send_recv(0x00 | (column & 0xF));
  spi_send_recv(0x10 | ((column >> 4) & 0xF));
  
  //display mode
  DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
}

void clear_display() {
  int r;
  for (r = 0; r<4; r++) {
    set_pos(0, r);
    
    //set everything to black
    int i;
    for (i = 0; i<128; i++) {
      spi_send_recv(0);
    }
  }
}

void draw_sprite(uint8_t x, uint8_t y, const int *sprite) {
  uint8_t width = (uint8_t)(sprite[METADATA]>>WIDTH);
  uint8_t height = (uint8_t)(sprite[METADATA]>>HEIGHT);
  uint8_t alpha = (uint8_t)(sprite[METADATA]>>ALPHA);

  uint8_t max_row = (y+height+7)/8;
  if (max_row > 4) max_row = 4;

  uint8_t max_column = width;
  if (max_column > 128 - x) max_column = 128-x;

  uint8_t row;
  for (row = y/8; row<max_row; row++) {
    
    set_pos(x, row);
    
    uint8_t column;
    for (column = 0; column<max_column; column++) {
      int c = sprite[column+IMAGE];
      int shift = ((int)(row*8)-y);
      uint8_t data;
      if (shift<0) data = (uint8_t)(c<<-shift);
      else data = (uint8_t)(c>>shift);
      
      spi_send_recv(data);
    }
  }
}

int main(void) {
  /* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	
	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
  SPI2CON |= 0x60;
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;
	
  //enable LEDs
  TRISE = 0;

	display_init();

  clear_display();

  uint8_t y = 0;
  uint8_t dy = 1;
  uint8_t x = 0;
  uint8_t dx = 1;

  //light a led
  PORTE = 1;
  
  while(1) {
    draw_sprite(0, 0, moduletest);

    draw_sprite(x, y, cursor);

    delay(100000);
    //draw_sprite(x, y, black16);
    y += dy;
    if (y == 0 || y == 16) dy *= -1;
    x += dx;
    if (x == 0 || x == 112) dx *= -1;

  }
  
  while(1) {
        
  }
  return 0;
}