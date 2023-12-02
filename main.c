#include <pic32mx.h>
#include <stdint.h>

#include "sprites.h"

#include "i2c.h"
#include "eeprom.h"
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

  screen_init();

  clear_screen();

  return 0;
}

void button_movement(uint8_t *cx, uint8_t *cy){
  //button movement
  // if (PORTD & (1 << 7)) {
  //     if (*cx>1) *cx -= 2;
  //   }

  //   if (PORTD & (1 << 6)){
  //     if (*cy > 0)
  //       *cy -= 1;
  //   }

  //   if (PORTD & (1 << 5)){
  //     if (*cy < 31)
  //       *cy += 1;
  //   }

  //   if (PORTF & (1 << 1)){
  //     if (*cx < 127)
  //       *cx += 2;
  //   }
  
  //switch movement
  if (PORTD & (1 << 11)) {
    if (*cx>0) *cx -= 1;
  }
  
  if (PORTD & (1 << 10)) {
    if (*cy>0) *cy -= 1;
  }

  if (PORTD & (1 << 9)) {
    if (*cy<31) *cy += 1;
  }

  if (PORTD & (1 << 8)) {
    if (*cx<127) *cx += 1;
  }
}

void save_state_eeprom(uint8_t* state, uint16_t time, int size){
  int i = 0;
  for (i = 0; i < size; i++){
    //fast använd page write istället.
    write_single_byte(i, state[i]);
  }
}

void draw_dummy_leds(const int *screen){
  uint8_t i = 0;
  for (i = 0; i < 8; i++){
    draw_sprite(10, i, led, screen);
  }
}

int main(void)
{
  // microcontroller setup for timers, interupts, i/o, i2c, spi, etc
  setup();
  //should be in setup
	uint8_t recieveBuffer = I2C1RCV; //Clear receive buffer

  
  uint8_t cy = 0;
  uint8_t cx = 0;

  //menu logic
  //while (inMenu) {menu boxes and The fun part yay}

  //start game routine
  uint8_t game = 1;

  uint16_t time = 900;
  uint8_t counter = 0;

  uint8_t selectedBits = 0xff;
  uint8_t bitPointer = 0;
  uint8_t PORTE8 = 0xff;

  int address = 0x0; //in total there are 32768 adresses. Each has 8 bits
  //write_single_byte(address, PORTE8);
  recieveBuffer = read_single_byte(address);
  uint8_t tempLed = 0xff; //initial values
  uint8_t selectedTempLed = 0xff;
  PORTE = 0b01001001;
  uint8_t lightsLed = PORTE; // sätt på alla ljus 1111 1111
  // skicka också ligihtsled till skärmen

  uint8_t currentModule = LIGHTS_OUT;

  int screen[128];

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
        while(1){

        }
    }
    
    //button movement
    button_movement(&cx, &cy);
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
    draw_digit(85, 3, recieveBuffer, screen);
    draw_digit(82, 3, recieveBuffer /10, screen);
    draw_digit(79, 3, recieveBuffer /100, screen);

    draw_digit(85, 10, address, screen);
    draw_digit(82, 10, address /10, screen);
    draw_digit(79, 10, address /100, screen);
    
    //draw_digit(76, 3, selectedBits, screen);
    counter++;
    if (counter > 59)
    {
      time -= 1;
      counter = 0;
    }
    draw_sprite(cx, cy, cursor, screen);
    present_screen(screen);

    //find out what module we are currently at, if even applicable.
    //switch (currentModule) {
    //  case (LIGHTS_OUT): 
    // check if solved, check if we have the correct entities 
    //    lights_out();
    //
    //}

    //lightsgame code
    if (counter%30 == 0 && btnPressed() != 0) //add gamemode toggle
    {
      draw_dummy_leds(screen);
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
      draw_sprite(10 + bitPointer * 14, 0, ledPointer, screen);
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
  

  while(1){

  }
  return 0;
}
