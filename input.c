#include <pic32mx.h>
#include <stdint.h>

#include "defs.h"

//move faster the longer a direction is held
uint8_t move_repeat(uint16_t time) {
  if (time == 0) return 0;
  if (time == 1) return 3;
  if ((time<=30) && (time>=15) && time%6==0) return 1;
  if ((time>30) && (time<=60) && time%3==0) return 1;
  if ((time>60) && time%2==0) return 1;
  //if (time>60) return 1;
  return 0;
}


void cursor_movement(uint8_t *cx, uint8_t *cy, const uint16_t *input){
  //switch movement
  *cx -= move_repeat(input[SWITCH4]);
  *cy -= move_repeat(input[SWITCH3]);
  *cy += move_repeat(input[SWITCH2]);
  *cx += move_repeat(input[SWITCH1]);

  if ((*cx > 127) && (*cx < 140)) *cx = 127;
  if (*cx > 140) *cx = 0;
  if ((*cy > 31) && (*cy < 120)) *cy = 31;
  if (*cy > 119) *cy = 0;
}

//get which buttons and switches are held and how long they've been
void get_input(uint16_t *input) {
  //buttons
  if (PORTD & (1 << 7)) {
    input[BUTTON4] += 1;
  } else input[BUTTON4] = 0;

  if (PORTD & (1 << 6)){
    input[BUTTON3] += 1;
  } else input[BUTTON3] = 0;

  if (PORTD & (1 << 5)){
    input[BUTTON2] += 1;
  } else input[BUTTON2] = 0;

  if (PORTF & (1 << 1)){
    input[BUTTON1] += 1;
  } else input[BUTTON1] = 0;

  //switches
  if (PORTD & (1 << 11)) {
    input[SWITCH4] += 1;
  } else input[SWITCH4] = 0;
  
  if (PORTD & (1 << 10)) {
    input[SWITCH3] += 1;
  } else input[SWITCH3] = 0;

  if (PORTD & (1 << 9)) {
    input[SWITCH2] += 1;
  } else input[SWITCH2] = 0;

  if (PORTD & (1 << 8)) {
    input[SWITCH1] += 1;
  } else input[SWITCH1] = 0;

  //pressing opposite directions result in no movement
  if (input[SWITCH4] && input[SWITCH1]) {
    input[SWITCH4] = 0;
    input[SWITCH1] = 0;
  }
  if (input[SWITCH3] && input[SWITCH2]) {
    input[SWITCH3] = 0;
    input[SWITCH2] = 0;
  }
}