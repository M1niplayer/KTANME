#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"
//#include "oled.h"

int screen[128];

void interrupt(void)
{
  // timerrrs
  return;
}

void delay(int cyc)
{
  int i;
  for (i = cyc; i > 0; i--);
}

int btnPressed()
{
  static uint8_t count = 0;
  //awful way of counting if you are not interrupting
  count += 1;
  if (count >= 200) return 0;
  count = 0;
  if ((PORTD & (1 << 5)) >> 5 == 1)
    return -1; // button 3

  if ((PORTD & (1 << 7)) >> 7 == 1)
    return 1; // butoton 1

  return 0;
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

  // enable LEDs
  TRISE = 0;

  display_init();

  clear_display();

  uint8_t y = 0;
  uint8_t dy = 1;
  uint8_t x = 0;
  uint8_t dx = 1;

  uint8_t game = 1;

  uint8_t lightsLed = 0xff; // sätt på alla ljus 1111 1111
  uint8_t selectedBits = 0xff;

  uint8_t tempLed = 0xff;
  uint8_t selectedTempLed = 0xff;
  PORTE = 0;
  // skicka också ligihtsled till skärmen

  while (game)
  {
    while (1)
    {
      // draw_sprite(0, 0, moduletest);

      // draw_sprite(x, y, cursor);

      set_background(screen, module_background);

      draw_sprite(x, y, cursor, screen);

      present_screen(screen);

      delay(100000);
      
      y += dy;
      if (y == 0 || y == 16)
      {
        dy *= -1;
      }
      x += dx;
      if (x == 0 || x == 112)
      {
        dx *= -1;
      }

      //if lightGamemode (btnPressed() == 0)

      //   tempLed = 0xff;
      //   selectedTempLed = 0xff;
      // if (bitPointer == 7 && btnPressed() == 1)
      // {
      //   // skip
      // }
      // else if (bitPointer == 0 && btnPressed() == -1)
      // {
      //   // skip
      // }
      // else
      // {
      //   bitPointer += btnPressed();
      // }
      // if (bitPointer >= 7)
      //   bitPointer = 7;
      // if (bitPointer <= 0)
      //   bitPointer = 0;
      // selectedBits = 0xff & (7 << lightsLed - 1);
      // if (bitPointer == 0)
      // {
      //   selectedBits = 0x11;
      // }

      // // e.g if selected bits is 00111000 then tempLed would be VV000VVVV
      // // where V is the current value of lightled
      // tempLed &= lightsLed & (0xff & ~selectedBits);
      // selectedTempLed = ~(lightsLed & selectedBits);
      // lightsLed = tempLed | selectedTempLed;
      // PORTE = lightsLed;
    }
  }

  if (lightsLed == 0)
    game = 0;

  // set_pos(120,0);
  // int i;
  // for (i = 0; i<17; i++) {
  //   spi_send_recv(9);
  // }

  // set_pos(120,1);
  // for (i = 0; i<17; i++) {
  //   spi_send_recv(9);
  // }

  // light a led

  // på något sätt visa vilket av ljusen man kommer släcka.
  //}


  while (1)
  {
  }
  return 0;
}
