#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"

#include "i2c.h"
#include "eeprom.h"
#include "highscore.h"
//#include "oled.h"

enum modules{
  LIGHTS_OUT,
  TEMPERATURE,
  POTENTIOMETER,
  SIMPLE_WIRES,
  EEPROM,
};

void interrupt(void)
{
  return;
}

void delay(int cyc)
{
  int i;
  for (i = cyc; i > 0; i--);
}

int setup(void){
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

  // reset timer
  T2CON = 0;
  TMR2 = 0;

  PR2 = 2604; // 80 000 000MHZ / 60HZ / 256 prescaling
  T2CONSET = 0x0070; //256 prescale
  T2CONSET = 0x8000; //start timer

  TRISE = 0;

  uint8_t recieveBuffer = I2C1RCV; //clear receive buffer

  screen_init();

  clear_screen();

  return 0;
}

int main(void)
{
  // microcontroller setup for timers, interupts, i/o, i2c, spi, etc
  setup();

  int screen[128];

  //cursor coordinates
  uint8_t cx = 0;
  uint8_t cy = 0;

  //menu logic
  //should show previous scores, difficulty settings, blabla
  set_background_pattern(0, screen);

  uint8_t l0 = 0;
  uint8_t l1 = 2;
  uint8_t l2 = 4;
  uint16_t time = 300;

  uint8_t pack0;
  uint8_t pack1;
  uint8_t pack2;
  pack_score(l0, l1, l2, time, &pack0, &pack1, &pack2);
  uint8_t c0 = 0;
  uint8_t c1 = 0;
  uint8_t c2 = 0;
  uint16_t t = 0;
  unpack_score(&c0, &c1, &c2, &t, pack0, pack1, pack2);
  
  draw_letter(0, 0, c0, screen);
  draw_letter(6, 0, c1, screen);
  draw_letter(12, 0, c2, screen);

  uint8_t seconds = t%60;
  uint8_t minutes = t/60;

  draw_digit(106, 3, minutes/10, screen);
  draw_digit(110, 3, minutes%10, screen);
  draw_digit(116, 3, seconds/10, screen);
  draw_digit(120, 3, seconds%10, screen);

  present_screen(screen);
  while(1) {

  }

  set_background(screen, menu);

  //game routine
  uint8_t game = 1;

  //uint16_t time = 900;
  uint8_t counter = 0;

  uint8_t selectedBits = 0xff;
  uint8_t bitPointer = 0;
  uint8_t PORTE8 = 0xff;

  uint8_t tempLed = 0xff; //initial values
  uint8_t selectedTempLed = 0xff;
  PORTE = 0b01001001;
  uint8_t lightsLed = PORTE; // sätt på alla ljus 1111 1111
  // skicka också ligihtsled till skärmen


  uint8_t test[64];
  uint8_t counterAgain = 0;
  for (counterAgain = 0; counterAgain < 64; counterAgain++){
    test[counterAgain] = counterAgain;
  }
  write_page(0x00000000, test);
  
  uint8_t output[64];
  read_page(0x00000000, output);
  output[0] = 9;

  uint8_t currentModule = LIGHTS_OUT;

  while (game)
  {

    //timer
    if ((IFS(0) & 0b100000000) == 0) {continue;}
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

        delay(animation_wait);
        
        game = 0;
        continue;
    }
    
    //cursor movement
    cursor_movement(&cx, &cy);
    set_background(screen, uidraft);

    uint8_t seconds = time%60;
    uint8_t minutes = time/60;
    
    //draw time
    draw_digit(106, 3, minutes/10, screen);
    draw_digit(110, 3, minutes%10, screen);
    draw_digit(116, 3, seconds/10, screen);
    draw_digit(120, 3, seconds%10, screen);

    //show what the bitpointer is at
    //throw in a help function so that my eyes don't hurt
    PORTE8 = PORTE & 0xff;
    //draw whatever. 
    draw_digit(85, 3, output[0], screen);
    draw_digit(82, 3, output[1] /10, screen);
    draw_digit(79, 3, output[2] /100, screen);
    draw_digit(76, 3, output[3] /100, screen);
    draw_digit(73, 3, output[4] /100, screen);
    
    //draw_digit(76, 3, selectedBits, screen);
    counter++;
    if (counter > 59)
    {
      time -= 1;
      counter = 0;
    }
    draw_sprite(cx, cy, cursor, screen);
    present_screen(screen);

    //lightsgame code
    if (counter%30 == 0 && btnPressed() != 0) //add gamemode toggle
    {
      //draw dummy leds
      // uint8_t i = 0;
      // for (i = 0; i < 8; i++){
      //   draw_sprite(2, 2+(i*9), led, screen);
      // }
      //pointer logic. 
      if (btnPressed() == 4 && bitPointer >= 7) ; //skip, too far to the left
      else if(btnPressed() == 1 && bitPointer == 0) ; //skip, too far to the right
      else{
        if (btnPressed() == 4) bitPointer += 1;
        if (btnPressed() == 1) bitPointer -= 1;
      }
      
      //selected bits logic
      selectedBits = 0xff & (7 << bitPointer - 1);
      if (bitPointer == 0){
        selectedBits = 0x3;
      }
      //draw pos of pointer
      //draw_sprite(10 + bitPointer * 14, 0, ledPointer, screen);
      //draw where your points is on the screen.
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

  //when finished, do highscore input.
  //to retry, press restart button

  while(1){

  }
  return 0;
}
