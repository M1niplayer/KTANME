#include <pic32mx.h>
#include <stdint.h>
#include <stdlib.h>
#include "sprites.h"

#include "i2c.h"
#include "eeprom.h"
#include "highscore.h"
#include "oled.h"
#include "temp.h"
#include "defs.h"
//möjligen kasta in i en const.h fil
uint8_t lightsOutSymbols[3] = {28, 49, 60};

enum modules{
  LIGHTS_OUT,
  TEMPERATURE,
  POTENTIOMETER,
  SIMPLE_WIRES,
  EEPROM,
};

enum difficulty{
  EASY,
  MEDIUM,
  HARD,
};

void *stdout = (void *) 0; //fixes stdout reference lmao

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
  //clear
  uint8_t recieveBuffer = I2C1RCV;
  PORTE = 0;

  //temperature config

  screen_init();

  clear_screen();

  return 0;
}

explode(const int *screen) {
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
}

//check if cursor is pressing button, 2=press, 1=hover over, 0=not hovering at
uint8_t virtual_button(uint8_t cx, uint8_t cy, uint8_t press, uint8_t btnX0, uint8_t btnY0, uint8_t btnX1, uint8_t btnY1) {
  if (cx >= btnX0 && cx <= btnX1 && cy >= btnY0 && cy <= btnY1) {
    if (press) {
      return 2;
    }
    return 1;
  }
  return 0;
}

uint8_t blink_led(uint8_t current, uint8_t selected){
  uint8_t tempLed;
  uint8_t selectedTempLed;
  tempLed = current & (0xff & ~selected); //set selected leds to 0
  selectedTempLed = ~current & selected; //invert selected leds in separate variable
  current = tempLed | selectedTempLed; //OR result together
  return current;
}

uint8_t calulate_solution(uint8_t symbol1, uint8_t symbol2){
  uint8_t solution = lightsOutSymbols[symbol1%3] + lightsOutSymbols[symbol2%3];
    switch(solution){
      case 56:
        return 0b00001001;
      case 77:
        return 0b01001000;
      case 88:
        return 0b00011000;
      case 98:
        return 0b10011001;
      case 109:
        return 0b00000100;
      case 120:
        return 0b00100100;
      default:
        return 0b00011000; //case 88
    }
}

void selectSymbol(int* symbolPic, uint8_t symbol){
  switch(symbol){
    case 0:
      symbolPic = square;
      break;
    case 1:
      symbolPic = grejs;
      break;
    case 2:
      symbolPic = stjarna;
      break;
    case 3:
      symbolPic = square2;
      break;
    case 4:
      symbolPic = grejs2;
      break;
    case 5:
      symbolPic = stjarna2;
      break;
    default:
      symbolPic = square;
      break;
  }
}
void uint8_to_binary(uint8_t number, uint8_t *binary) {
  uint8_t i = 0;
  for (i = 0; i < 8; i++) {
    binary[i] = (number >> i) & 1;
  }
}

uint8_t stars_to_solved(const uint8_t *stars) {
  uint8_t i = 0;
  uint8_t solved*;
  uint8_t leftCount = 0;
  uint8_t rightCount = 0;;
  for (i = 0; i < 4; i++) {
    if (stars[i]) leftCount++;
  }
  for (i = 4; i < 8; i++) {
    if (stars[i]) rightCount++;
  }
  uint8_t count = leftCount + rightCount;
  
  //logic
  if (stars[0]) solved[0] = 0;
  else {solved[0] = 1; solved[3] = 0;}

  if (count > 4){solved[2] = 0; solved[6] = 1;}
  else if (count < 3){solved[2] = 1;}
  else {solved[2] = 0;}

  if (stars[4] && (stars[3] || stars[5])) {solved[4] = 1; solved[5] = 0;}
  else if (stars[4]) solved[7] = 0;
  else if (!stars[4]) solved[5] = 1;

  if (!stars[5]) solved[6] = 0; 
  else {
    //cut all even wires
    solved[1] = 0;
    solved[3] = 0;
    solved[5] = 0;
    solved[7] = 0;
  }

  if (rightCount > leftCount) {solved[1] = 1; solved[3] = 1;
  else {solved[1] = 0; solved[3] = 0;}

  if ((!stars[5]) || (!stars[7])) solved[7] = 0; 
  else solved[4] = 1;
  
  if (!stars[1]) solved[4] = 0; solved[6] = 0;
  else solved[4] = 1; solved[6] = 0;
  return solved;
  }
}

int main(void)
{
  // microcontroller setup for timers, interupts, i/o, i2c, spi, etc
  setup();
  //pseudorandomness
  uint8_t seed = 0;
  int screen[128];
  uint8_t input[8];

  //cursor coordinates
  uint8_t cx = 32;
  uint8_t cy = 16;


  set_temp_config(0b00100000); //0.25c resolution
  set_temp_limits(-30, 60);

  //intro sequence / startup goes here
  //A GAME BY Jimmy & Erik
  //The manual is for the bomb defuser's eyes ONLY

  //menu logic
  //should show previous scores, difficulty settings, blabla
  set_background_pattern(0, screen);
  present_screen(screen);
  //does not repeat
  while(1) {
    PORTE = 0;
    uint8_t counter = 0;
    uint8_t difficulty = EASY;

    uint8_t inMenu = 1;
    while (inMenu) {
      //timer
      
      seed += 1;
      if ((IFS(0) & 0b100000000) == 0) {continue;}
      IFSCLR(0) = 0b100000000;

      counter++;
      if (counter > 59)
      {
        counter = 0;
      }

      get_input(input);

      uint8_t pointing = 0;
      uint8_t press = (PORTD & (1 << 7));

      uint8_t buttonPress = virtual_button(cx, cy, press, 2, 7, 28, 13);
      if (buttonPress) pointing = 1;
      if (buttonPress == 2) {
        difficulty = EASY;
        inMenu = 0;
      }

      buttonPress = virtual_button(cx, cy, press, 2, 15, 28, 21);
      if (buttonPress) pointing = 1;
      if (buttonPress == 2) {
        difficulty = MEDIUM;
        inMenu = 0;
      }

      buttonPress = virtual_button(cx, cy, press, 2, 13, 28, 29);
      if (buttonPress) pointing = 1;
      if (buttonPress == 2) {
        difficulty = HARD;
        inMenu = 0;
      }

      cursor_movement(&cx, &cy, input);
      set_background(screen, menu);
      if (pointing) draw_sprite(cx, cy, cursor_pointing, screen);
      else draw_sprite(cx, cy, cursor, screen);
      present_screen(screen);
    }
    PORTE = 0;
    //gameSetup
    srand(seed);
    
    uint16_t time = 900 - (difficulty*300);
    counter = 0;
    uint8_t selectedBits = 0xff;
    //lights game
    uint8_t bitPointer = 0;
    uint8_t PORTE8 = 0;
    //temp module
    uint8_t temperature = 0;
    //0, 25, 50, 100
    uint8_t tempDecimals = 0; 
    bool tempHot = false;
    
    uint8_t game = 1;

    //wires logic lmao
    uint8_t wire[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t solvedWires[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t stars[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t temperatureSeed = rand()%255;
    uint8_t starCount = 0;
    uint8_t wirePosition = 0;
    uint8_t temperatureSolved = 0;
    uint8_t i = 0;
    uint8_to_binary(temperatureSeed, stars);
    for (i = 0; i < 8; i++) {
      if (stars[i]) starCount++;
    }
    temperatureSolved = stars_to_solved(stars, starCount);
    uint8_to_binary(temperatureSolved, solvedWires);


    //solvedled logic
    uint8_t symbol1 = rand()%6; //6 different symbols
    uint8_t symbol2 = rand()%6;
    
    uint8_t solvedLed = calulate_solution(symbol1, symbol2);  
     
    //int symbolPic1 [33];
    //int symbolPic2 [33];
    //selectSymbol(symbolPic1, symbol1);
    //selectSymbol(symbolPic2, symbol2); 
    while (game) {
      //timer
      if ((IFS(0) & 0b100000000) == 0) {continue;}
      IFSCLR(0) = 0b100000000;

      //win condition, solve all modules
      if (PORTE8 == solvedLed) {
        game = 0;
        continue;
      }

      //lose condition
      if (time == 0) {
        explode(screen);
        
        game = 0;
        continue;
      }

      get_input(input);
      
      //cursor movement
      cursor_movement(&cx, &cy, input);
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
      //draw whatever. 
      
      counter++;
      if (counter > 59)
      {
        time -= 1;
        counter = 0;
      }
      draw_sprite(cx, cy, cursor, screen);

      //show temp routine
      temperature = read_temp();
      //since we don't change tempconfig, hardcode solution
      tempDecimals = (temperature & 0x3) * 25; 
      draw_digit(76, 3, tempDecimals, screen);
      draw_digit(72, 3, tempDecimals/10, screen);
      //draw comma
      temperature = temperature >> 1;
      draw_digit(69, 3, temperature >> 1, screen);
      draw_digit(65, 3, (temperature >> 1)/10, screen);
      //bool hotBefore = false;
      //modify wires routine
      if (temperature > 28 ) { //&& !hotBefore
        tempHot = true;
        //hotBefore = true;
      }

      if (tempHot || input[BUTTON3] == 1) {
        //check if valid cursor position : return what position as uint8_t
        if(tempHot){wire[wirePosition] = 1;} //solder
        else if(input[BUTTON3] == 1){wire[wirePosition] = 0;} //cut
      }

    


      if () {
        //cut wire
      }
      present_screen(screen);
    }

    //when finished, do highscore input.
    //to retry, press restart button
  }
  return 0;
}
