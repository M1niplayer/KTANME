#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"
//#include "oled.h"

void interrupt(void)
{
  //timerrrs
  return;
}

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

int btnPressed(){
  if (PORTD & 0b0010000 == 1) return -1; //button 1
  
  if (PORTD & 0b1000000 == 1) return 1; //butoton 4
}

int main(void) {
  //SETUP

  /* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;       //leds
	
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


  uint8_t game = 1;

  uint8_t lightsLed = 0xff; //sätt på alla ljus 1111 1111
  uint8_t selectedBits = 0xff;
  PORTE = lightsLed;
  //skicka också ligihtsled till skärmen
  uint8_t bitPointer = 0; //go from 0-7, corresponding to each bit in lightsled
  
  while(game) {

    //update sprite hjälpfunktion?

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

    //if lightGamemode
    if (bitPointer != 7 || bitPointer != 0) {
      bitPointer += btnPressed(); //either 1 or -1
    }
    if (lightsLed == 0){
      lightsLed = ~lightsLed;
    }
      //7 is 111, so this will light up select bit + adjacent, except for special case 0
      selectedBits  = 0xff & (7 << lightsLed - 1);
      lightsLed = ~selectedBits;
    }
  
    if (lightsLed == 0) game = 0;
  
  
    //light a led
  
    //på något sätt visa vilket av ljusen man kommer släcka. 
  
  }
  

  while(1) {
        
  }
  return 0;
}
