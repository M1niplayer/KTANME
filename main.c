#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"

#include "i2c.h"
#include "eeprom.h"
// #include "oled.h"

int screen[128];

void interrupt(void)
{
  // timerrrs
  return;
}

void delay(int cyc)
{
  int i;
  for (i = cyc; i > 0; i--)
    ;
}

int btnPressed()
{
  if (PORTF & (1 << 1))
    return 1; // BTN1

  if (PORTD & (1 << 5))
    return 2; // BTN2

  if (PORTD & (1 << 6))
   return 3; // BTN3

  if (PORTD & (1 << 7))
    return 4; // BTN4

  return 0;
}

int main(void)
{
  // SETUP

  /* Set up peripheral bus clock */
  OSCCON &= ~0x180000;
  OSCCON |= 0x080000;

  /* Set up output pins */
  AD1PCFG = 0xFFFF;
  ODCE = 0x0;
  TRISECLR = 0xFF;
  PORTE = 0x0; // leds

  /* Output pins for display signals */
  PORTF = 0xFFFF;
  PORTG = (1 << 9);
  ODCF = 0x0;
  ODCG = 0x0;
  TRISFCLR = 0x70;
  TRISGCLR = 0x200;

  /* Set up input pins */
  TRISDSET = (111 << 5);
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

  /* Set up i2c */
	I2C1CON = 0x0;
	/* uh, actually I don't know if the baud rate generator has to be less than 
  khz, it's just that it only operates at either 100 or 400 khz*/
	I2C1BRG = 0x0C2;
	I2C1STAT = 0x0;
	I2C1CONSET = 1 << 13; //SIDL = 1
	I2C1CONSET = 1 << 15; // ON = 1
	int32_t recieveBuffer = I2C1RCV; //Clear receive buffer

  // reset timer
  T2CON = 0;
  TMR2 = 0;

  PR2 = 5208;        // 80 000 000MHZ / 10HZ / 256 prescaling
  T2CONSET = 0x0070; // 256 prescale
  T2CONSET = 0x8000; // start timer

  // enable LEDs
  TRISE = 0;

  display_init();

  clear_display();

  uint8_t cy = 0;
  uint8_t cx = 0;

  uint8_t game = 1;

  uint16_t time = 900;
  uint8_t counter = 0;

  uint8_t selectedBits = 0xff;
  uint8_t bitPointer = 0;
  uint8_t PORTE8 = 0;


  int address = 0x0;
  
  recieveBuffer = read_byte(address);
  uint8_t tempLed = 0xff; //initial values
  uint8_t selectedTempLed = 0xff;
  //PORTE = 0b01001001;
  uint8_t lightsLed = PORTE; // sätt på alla ljus 1111 1111
  // skicka också ligihtsled till skärmen

  while (game)
  {
    if ((IFS(0) & 0b100000000) != 0)
    {
      IFSCLR(0) = 0b100000000;

      if (PORTD & (1 << 7))
      {
        if (cx > 1)
          cx -= 2;
      }

      if (PORTD & (1 << 6))
      {
        if (cy > 0)
          cy -= 1;
      }

      if (PORTD & (1 << 5))
      {
        if (cy < 31)
          cy += 1;
      }

      if (PORTF & (1 << 1))
      {
        if (cx < 127)
          cx += 2;
      }

      // switches

      // time logic
      set_background(screen, uidraft);

      draw_sprite(cx, cy, cursor, screen);

      uint8_t seconds = time % 60;
      uint8_t minutes = time / 60;
      draw_digit(106, 3, btnPressed(), screen);
      //draw_digit(106, 3, minutes / 10, screen);
      draw_digit(110, 3, minutes % 10, screen);
      draw_digit(116, 3, seconds / 10, screen);
      draw_digit(120, 3, seconds % 10, screen);

      //show what the bitpointer is at
      //throw in a help function so that my eyes don't hurt
      PORTE8 = PORTE & 0xff;
      PORTE |= 0x01;
      PORTE |= 0x80;
      draw_digit(85, 3, recieveBuffer, screen);
      draw_digit(82, 3, recieveBuffer /10, screen);
      draw_digit(79, 3, recieveBuffer /100, screen);
      //draw_digit(76, 3, selectedBits, screen);
      counter++;
      if (counter > 59)
      {
        time -= 1;
        counter = 0;
      }
      present_screen(screen);


      //lightsgame code
      if (counter%30 == 0 && btnPressed() != 0) //add gamemode toggle
      {
        //pointer logic. 
        if (btnPressed() == 4 && bitPointer >= 7) ; //skip
        else if(btnPressed() == 1 && bitPointer == 0) ; //skip 
        else{
          if (btnPressed() == 4) bitPointer += 1;
          if (btnPressed() == 1) bitPointer -= 1;
        }
        
        //selected bits logic
        selectedBits = 0xff & (7 << bitPointer - 1);
        if (bitPointer == 0)
        {
          selectedBits = 0x3;
        }
        

        // e.g if selected bits is 00111000 then tempLed would be VV000VVVV
        // where V is the current value of lightled
        if (btnPressed() == 3){
          tempLed = lightsLed & (0xff & ~selectedBits);
          selectedTempLed = ~lightsLed & selectedBits;
          lightsLed = tempLed | selectedTempLed;

          PORTE = lightsLed;
        }
      }
    }
  }

  // light a led

  // på något sätt visa vilket av ljusen man kommer släcka.
  //}

  while (1)
  {
  }
  return 0;
}
