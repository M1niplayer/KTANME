#include <pic32mx.h>
#include <stdint.h>
#include <string.h>
#include "sprites.h"

#include "i2c.h"
#include "eeprom.h"
#include "highscore.h"
//#include "oled.h"

#include "defs.h"

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
uint8_t virtual_button(uint8_t cx, uint8_t cy, uint8_t btnX0, uint8_t btnY0, uint8_t btnX1, uint8_t btnY1) {
  if (cx >= btnX0 && cx <= btnX1 && cy >= btnY0 && cy <= btnY1) {
    return 1;
  }
  return 0;
}

int main(void)
{
  
  // microcontroller setup for timers, interupts, i/o, i2c, spi, etc
  setup();
  int screen[128];

  uint16_t input[8];
  
  //write_page(0x0000, empty);
  
  //cursor coordinates
  uint8_t cx = 32;
  uint8_t cy = 16;

  //intro sequence / startup goes here
  //A GAME BY Jimmy & Erik
  //Keep the manual close at hand

  //menu logic
  set_background_pattern(0, screen);

  present_screen(screen);

  uint8_t highscores[41];

  //write_page(0x0000, empty);

  while(1) {
    PORTE++;
    load_highscore(highscores);
    uint8_t counter = 0;
    uint8_t difficulty = EASY;

    uint8_t inMenu = 1;
    while (inMenu) {
      //timer
      if ((IFS(0) & 0b100000000) == 0) {continue;}
      IFSCLR(0) = 0b100000000;

      counter++;
      if (counter > 59)
      {
        counter = 0;
      }

      get_input(input);

      uint8_t pointing = 0;
      uint8_t press = (input[BUTTON4]==1);

      uint8_t buttonPress = virtual_button(cx, cy, 2, 7, 28, 13);
      if (buttonPress) {
        pointing = 1;
        if (press) {
          difficulty = EASY;
          inMenu = 0;
        }
      }

      buttonPress = virtual_button(cx, cy, 2, 15, 28, 21);
      if (buttonPress) {
        pointing = 1;
        if (press) {
          difficulty = MEDIUM;
          inMenu = 0;
        }
      }

      buttonPress = virtual_button(cx, cy, 2, 13, 28, 29);
      if (buttonPress) {
        pointing = 1;
        if (press) {
          difficulty = HARD;
          inMenu = 0;
        }
      }

      set_background(screen, menu);
      //show highscores
      uint8_t i;
      //first 

      for (i = 0; i<4; i++) {
        //if (highscores[0] <i+1) break;

        uint16_t time = highscores[(i*5)+5] + highscores[(i*5)+4]<<8;

        uint8_t seconds = time%60;
        uint8_t minutes = time/60;
        
        draw_digit(37, 7+(i*6), i+1, screen);

        //draw time
        draw_digit(63, 7+(i*6), minutes/10, screen);
        draw_digit(67, 7+(i*6), minutes%10, screen);
        draw_digit(73, 7+(i*6), seconds/10, screen);
        draw_digit(77, 7+(i*6), seconds%10, screen);
        

        draw_letter(43, 7+(i*6), highscores[(i*5)+1], screen);
        draw_letter(49, 7+(i*6), highscores[(i*5)+2], screen);
        draw_letter(55, 7+(i*6), highscores[(i*5)+3], screen);
      }
      //last 4
      for (i = 0; i<4; i++) {
        //if (highscores[0] <i+5) break;

        uint16_t time = highscores[((i+4)*5)+5] + highscores[((i+4)*5)+4]<<8;

        uint8_t seconds = time%60;
        uint8_t minutes = time/60;
        
        draw_digit(37+46, 7+(i*6), i+5, screen);

        //draw time
        draw_digit(63+46, 7+(i*6), minutes/10, screen);
        draw_digit(67+46, 7+(i*6), minutes%10, screen);
        draw_digit(73+46, 7+(i*6), seconds/10, screen);
        draw_digit(77+46, 7+(i*6), seconds%10, screen);
        

        draw_letter(43+46, 7+(i*6), highscores[((i+4)*5)+1], screen);
        draw_letter(49+46, 7+(i*6), highscores[((i+4)*5)+2], screen);
        draw_letter(55+46, 7+(i*6), highscores[((i+4)*5)+3], screen);
      }

      draw_digit(29, 3, highscores[0], screen);
      draw_digit(26, 3, highscores[0]/10, screen);

      //draw_digit(90, 3, read_single_byte(0x0001), screen);
      //draw_digit(87, 3, read_single_byte(0x0001)/10, screen);
      //draw_digit(84, 3, read_single_byte(0x0002), screen);
      //draw_digit(81, 3, read_single_byte(0x0002)/10, screen);
      
      cursor_movement(&cx, &cy, input);
      if (pointing) draw_sprite(cx, cy, cursor_pointing, screen);
      else draw_sprite(cx, cy, cursor, screen);
      present_screen(screen);
    }

    uint8_t win = 1;

    uint16_t time = 900 - (difficulty*300);
    counter = 0;

    uint8_t selectedBits = 0xff;
    uint8_t bitPointer = 0;
    uint8_t PORTE8 = 0xff;

    uint8_t tempLed = 0xff; //initial values
    uint8_t selectedTempLed = 0xff;
    uint8_t solvedLed = 0b01001001;
    uint8_t lightsLed = PORTE; // sätt på alla ljus 1111 1111
    // skicka också ligihtsled till skärmen

    uint8_t currentModule = LIGHTS_OUT;

    uint8_t game = 1;

    while (game) {
      //timer
      if ((IFS(0) & 0b100000000) == 0) {continue;}
      IFSCLR(0) = 0b100000000;

      //win condition, solve all modules
      if (win) {
        game = 0;

        //win sequence
        //win screen, score, then input name
        uint8_t name[3];
        name[0] = 255;
        name[1] = 255;
        name[2] = 255;
        uint8_t nameInput = 1;
        while(nameInput) {
          //timer
          if ((IFS(0) & 0b100000000) == 0) {continue;}
          IFSCLR(0) = 0b100000000;

          uint8_t pointing = 0;
          uint8_t press = (input[BUTTON4]==1);
          uint8_t backPress = (input[BUTTON3]==1);
          get_input(input);
          cursor_movement(&cx, &cy, input);
          uint8_t selectedLetter = 255;
          uint8_t i;

          //first row of letters
          for (i = 0; i<13; i++) {
            uint8_t lx = 2 + (9*i);
            if (virtual_button(cx, cy, lx, 12, lx+6, 18)) {
              pointing = 1;
              if (press) {
                selectedLetter = i;
              }
            }
          }

          //second row
          for (i = 0; i<13; i++) {
            uint8_t lx = 2 + (9*i);
            if (virtual_button(cx, cy, lx, 21, lx+6, 27)) {
              pointing = 1;
              if (press) {
                selectedLetter = i+13;
              }
            }
          }

          if (virtual_button(cx, cy, 119, 12, 124, 18)) {
            pointing = 1;
            if (press) {
              selectedLetter = 254;
            }
          }

          if (virtual_button(cx, cy, 96, 3, 120, 9)) {
            pointing = 1;
            if (press) {
              selectedLetter = 253;
            }
          }

          if ((selectedLetter == 254) || backPress) {
            uint8_t c;
            for (c = 0; c<3; c++) {
              if (name[2-c] != 255) {
                name[2-c] = 255;
                break;
              }
            }
          } else if (selectedLetter == 253) {
            if (name[2] != 255) {
              nameInput = 0;
              
              uint16_t score = time;
              if (difficulty == EASY) score /= 3;
              else if (difficulty == MEDIUM) score /= 2;
              if (score > 899) score = 899;
              save_highscore(name[0], name[1], name[2], score);
              continue;
            }
          } else if (selectedLetter != 255) {
            uint8_t c;
            for (c = 0; c<3; c++) {
              if (name[c] == 255) {
                name[c] = selectedLetter;
                break;
              }
            }
          }

          set_background(screen, keyboard);

          if (name[0] != 255) {
            draw_letter(60, 2, name[0], screen);
          }
          if (name[1] != 255) {
            draw_letter(66, 2, name[1], screen);
          }
          if (name[2] != 255) {
            draw_letter(72, 2, name[2], screen);
          }

          if (pointing) draw_sprite(cx, cy, cursor_pointing, screen);
          else draw_sprite(cx, cy, cursor, screen);
          present_screen(screen);
        }

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
      PORTE8 = PORTE & 0xff;
      //draw whatever. 
      draw_digit(85, 3, bitPointer, screen);
      draw_digit(82, 3, bitPointer /10, screen);
      draw_digit(79, 3, bitPointer /100, screen);
      
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
      // if ((counter%30 == 0) && (btnPressed() != 0)) //add gamemode toggle
      // {
      //   //draw dummy leds
      //   uint8_t i = 0;
      //   for (i = 0; i < 8; i++){
      //     draw_sprite(2+(i*9), 2, led, screen);
      //   }
      //   draw_sprite(2+(bitPointer*9), 2, ledPointer, screen);

      //   //pointer logic. 
      //   if (btnPressed() == 4 && bitPointer >= 7) ; //skip, too far to the left
      //   else if(btnPressed() == 1 && bitPointer == 0) ; //skip, too far to the right
      //   else{
      //     if (btnPressed() == 4) bitPointer += 1;
      //     if (btnPressed() == 1) bitPointer -= 1;
      //   }
        
      //   //selected bits logic
      //   selectedBits = 0xff & (7 << bitPointer - 1);
      //   if (bitPointer == 0){
      //     selectedBits = 0x3;
      //   }
      //   //draw pos of pointer
      //   //draw_sprite(10 + bitPointer * 14, 0, ledPointer, screen);
      //   //draw where your points is on the screen.
      //   // e.g if selected bits is 00111000 then tempLed would be VV000VVVV
      //   // where V is the current value of lightled
      //   if (btnPressed() == 3){
      //     tempLed = lightsLed & (0xff & ~selectedBits);
      //     selectedTempLed = ~lightsLed & selectedBits;
      //     lightsLed = tempLed | selectedTempLed;

      //     PORTE = lightsLed;
      //   }
      // }
    }

    //when finished, do highscore input.
    //to retry, press restart button
  }
  return 0;
}