#include <pic32mx.h>
#include <stdint.h>

const uint8_t const num[30] = {0b00001110, 0b00010001, 0b00001110, 0b00000010, 0b00011111, 0b00000000, 0b00010010, 0b00011001, 0b00010110, 0b00010001, 0b00010101, 0b00001010, 0b00000111, 0b00000100, 0b00011111, 0b00010111, 0b00010101, 0b00001001, 0b00001110, 0b00010101, 0b00001000, 0b00000001, 0b00011001, 0b00000111, 0b00001010, 0b00010101, 0b00001010, 0b00000010, 0b00010101, 0b00001110};

const uint8_t const font[130] = {0b00011100, 0b00001010, 0b00001001, 0b00001010, 0b00011100, 0b00011111, 0b00010101, 0b00010101, 0b00010101, 0b00001010, 0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00001010, 0b00011111, 0b00010001, 0b00010001, 0b00010001, 0b00001110, 0b00011111, 0b00010101, 0b00010101, 0b00010101, 0b00010001, 0b00011111, 0b00000101, 0b00000101, 0b00000101, 0b00000001, 0b00001110, 0b00010001, 0b00010001, 0b00010101, 0b00001101, 0b00011111, 0b00000100, 0b00000100, 0b00000100, 0b00011111, 0b00010001, 0b00010001, 0b00011111, 0b00010001, 0b00010001, 0b00001000, 0b00010000, 0b00010001, 0b00001111, 0b00000001, 0b00011111, 0b00000100, 0b00000100, 0b00001010, 0b00010001, 0b00011111, 0b00010000, 0b00010000, 0b00010000, 0b00010000, 0b00011111, 0b00000001, 0b00000010, 0b00000001, 0b00011111, 0b00011111, 0b00000010, 0b00000100, 0b00001000, 0b00011111, 0b00001110, 0b00010001, 0b00010001, 0b00010001, 0b00001110, 0b00011111, 0b00000101, 0b00000101, 0b00000101, 0b00000010, 0b00001110, 0b00010001, 0b00010001, 0b00001001, 0b00010110, 0b00011111, 0b00000101, 0b00000101, 0b00000101, 0b00011010, 0b00010010, 0b00010101, 0b00010101, 0b00010101, 0b00001001, 0b00000001, 0b00000001, 0b00011111, 0b00000001, 0b00000001, 0b00001111, 0b00010000, 0b00010000, 0b00010000, 0b00001111, 0b00000011, 0b00001100, 0b00010000, 0b00001100, 0b00000011, 0b00001111, 0b00010000, 0b00001000, 0b00010000, 0b00001111, 0b00010001, 0b00001010, 0b00000100, 0b00001010, 0b00010001, 0b00000001, 0b00000010, 0b00011100, 0b00000010, 0b00000001, 0b00010001, 0b00011001, 0b00010101, 0b00010011, 0b00010001};

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

//oled screen communication
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void screen_init() {
  //THIS CODE IS FROM THE COURSE EXAMPLES, NOT BY US
  
  //power on sequence
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

  //BACK TO OUR OWN CODE AGAIN

  //Page addressing mode
  //command mode
  DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
  //set addressing mode
  spi_send_recv(0x20);
  //page addressing code
  spi_send_recv(0x10);
  //display mode
  DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
}

//move screen pointer to specific place
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

//fill screen with white, black, or stripes
void fill_screen(uint8_t pattern) {
  int r;
  for (r = 0; r<4; r++) {
    set_pos(0, r);
    
    int i;
    for (i = 0; i<128; i++) {
      spi_send_recv(pattern);
    }
  }
}

void clear_screen() {
  //set everything to black
  fill_screen(0);
}

//draw 128x32 sprite to fill whole screen
void set_background(int *screen, const int *background) {
  uint8_t i;
  for (i = 0; i<128; i++) {
    screen[i] = background[i];
  }
}

//fill screen with striped pattern
void set_background_pattern(int pattern, int *screen) {
  uint8_t i;
  for (i = 0; i<128; i++) {
    screen[i] = pattern;
  }
}

//take the int array other functions operate on and push it to the real oled screen
void present_screen(const int *screen) {
  uint8_t row;
  for (row = 0; row<4; row++) {
    
    set_pos(0, row);
    
    uint8_t column;
    for (column = 0; column<128; column++) {
      int c = screen[column];
      int shift = (int)(row*8);
      uint8_t data;
      if (shift<0) data = (uint8_t)(c<<-shift);
      else data = (uint8_t)(c>>shift);
      
      spi_send_recv(data);
    }
  }
}

//draw a sprite to screen, transparency support
void draw_sprite(uint8_t x, uint8_t y, const int *sprite, int *screen) {
  uint8_t width = (uint8_t)(sprite[METADATA]>>WIDTH);
  uint8_t height = (uint8_t)(sprite[METADATA]>>HEIGHT);
  uint8_t alpha = (uint8_t)(sprite[METADATA]>>ALPHA);

  uint8_t max_column = width;
  if (max_column + x > 128) max_column = 128-x;

  if (alpha) {
    uint8_t column;
    for (column = 0; column<max_column; column++) {

      int sprite_c = sprite[column+IMAGE];
      int sprite_a = sprite[column+IMAGE+width];
      
      screen[x+column] = ((screen[x+column] & (~(sprite_a<<y))) | (sprite_c<<y)); //((sprite_c & sprite_a)<<y))
    }
  } else {
    uint8_t column;
    for (column = 0; column<max_column; column++) {

      int sprite_c = sprite[column+IMAGE];

      screen[x+column] = sprite_c<<y; //((sprite_c & sprite_a)<<y))
    }
  }
}

//draw a single digit to screen
void draw_digit(uint8_t x, uint8_t y, uint8_t digit, int *screen) {
  digit = digit%10;
  uint8_t column;
  for (column = 0; column<128-x; column++) {
    if (column>2) break;
    int digit_c = num[(digit*3)+column];
    
    screen[x+column] = ((screen[x+column] & (~(0x1f<<y))) | ((int)digit_c<<y));
  }
}

//draw a single letter to screen
void draw_letter(uint8_t x, uint8_t y, uint8_t letter, int *screen) {
  letter = letter%26;
  uint8_t column;
  for (column = 0; column<128-x; column++) {
    if (column>4) break;
    int letter_c = font[(letter*5)+column];
    
    screen[x+column] = ((screen[x+column] & (~(0x1f<<y))) | ((int)letter_c<<y));
  }
}


// old draw sprite that does not need int[128] of screen, no transparency support

// print a sprite directly to anywhere on the oled screen, but overwrites the columns it overlaps
// void draw_sprite(uint8_t x, uint8_t y, const int *sprite) {
//   uint8_t width = (uint8_t)(sprite[METADATA]>>WIDTH);
//   uint8_t height = (uint8_t)(sprite[METADATA]>>HEIGHT);
//   uint8_t alpha = (uint8_t)(sprite[METADATA]>>ALPHA);

//   uint8_t max_row = (y+height+7)/8;
//   if (max_row > 4) max_row = 4;

//   uint8_t max_column = width;
//   if (max_column > 128 - x) max_column = 128-x;

//   uint8_t row;
//   for (row = y/8; row<max_row; row++) {
    
//     set_pos(x, row);
    
//     uint8_t column;
//     for (column = 0; column<max_column; column++) {
//       int c = sprite[column+IMAGE];
//       int shift = ((int)(row*8)-y);
//       uint8_t data;
//       if (shift<0) data = (uint8_t)(c<<-shift);
//       else data = (uint8_t)(c>>shift);
      
//       spi_send_recv(data);
//     }
//   }
// }