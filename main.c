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

  //reset timer
  T2CON = 0;
  TMR2 = 0;

  PR2 = 2604; // 80 000 000MHZ / 60HZ / 256 prescaling
  T2CONSET = 0x0070; //256 prescale
  T2CONSET = 0x8000; //start timer

  // enable LEDs
  TRISE = 0;

  screen_init();

  clear_screen();

  uint8_t cy = 0;
  uint8_t cx = 0;

  uint8_t game = 1;

  uint16_t time = 2; //900;
  uint8_t counter = 0;

  uint8_t lightsLed = 0xff; // sätt på alla ljus 1111 1111
  uint8_t selectedBits = 0xff;

  uint8_t tempLed = 0xff;
  uint8_t selectedTempLed = 0xff;
  PORTE = 0;
  // skicka också ligihtsled till skärmen

  while (game)
  {
    if ((IFS(0) & 0b100000000) != 0) {
      IFSCLR(0) = 0b100000000;

      if (time == 0) {
        int animation_wait = 1000000;
        clear_screen();
        
        delay(animation_wait);

        set_background_pattern(0, screen);
        draw_sprite(63, 0, explode_animation0, screen);
        present_screen(screen);

        delay(animation_wait);

        draw_sprite(62, 0, explode_animation1, screen);
        present_screen(screen);

        delay(animation_wait);

        set_background_pattern(0, screen);
        draw_sprite(63, 0, explode_animation0, screen);
        present_screen(screen);

        delay(animation_wait);

        clear_screen();

        delay(animation_wait);

        set_background_pattern(0, screen);
        draw_sprite(63, 0, explode_animation0, screen);
        present_screen(screen);

        delay(animation_wait);

        draw_sprite(61, 0, explode_animation1, screen);
        present_screen(screen);

        delay(animation_wait);

        draw_sprite(56, 0, explode_animation2, screen);
        present_screen(screen);

        delay(animation_wait);

        draw_sprite(51, 0, explode_animation3, screen);
        present_screen(screen);

        delay(animation_wait);

        draw_sprite(40, 0, explode_animation4, screen);
        present_screen(screen);

        delay(animation_wait);

        set_background_pattern(0, screen);
        draw_sprite(11, 0, explode_animation5, screen);
        present_screen(screen);

        delay(animation_wait);

        set_background_pattern(0, screen);
        draw_sprite(6, 0, explode_animation6, screen);
        present_screen(screen);

        delay(animation_wait);

        fill_screen(0xff);

        delay(animation_wait*5);

        fill_screen(0xee);

        delay(animation_wait);

        fill_screen(0x55);

        delay(animation_wait);

        fill_screen(0x11);

        delay(animation_wait);
        
        clear_screen();
        while(1){

        }
      }

      //button movement
      if (PORTD & (1 << 7)) {
        if (cx>1) cx -= 2;
      }
      
      if (PORTD & (1 << 6)) {
        if (cy>0) cy -= 1;
      }

      if (PORTD & (1 << 5)) {
        if (cy<31) cy += 1;
      }

      if (PORTF & (1 << 1)) {
        if (cx<127) cx += 2;
      }

      //switch movement
      // if (PORTD & (1 << 11)) {
      //   if (cx>0) cx -= 1;
      // }
      
      // if (PORTD & (1 << 10)) {
      //   if (cy>0) cy -= 1;
      // }

      // if (PORTD & (1 << 9)) {
      //   if (cy<31) cy += 1;
      // }

      // if (PORTD & (1 << 8)) {
      //   if (cx<127) cx += 1;
      // }

      set_background(screen, uidraft);

      uint8_t seconds = time%60;
      uint8_t minutes = time/60;
      draw_digit(106, 3, minutes/10, screen);
      draw_digit(110, 3, minutes%10, screen);
      draw_digit(116, 3, seconds/10, screen);
      draw_digit(120, 3, seconds%10, screen);
      counter ++;
      if (counter>=60) {
        time -= 1;
        counter = 0;
      }
      draw_sprite(cx, cy, cursor, screen);
      present_screen(screen);

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

  // light a led

  // på något sätt visa vilket av ljusen man kommer släcka.
  //}


  while (1)
  {
  }
  return 0;
}
