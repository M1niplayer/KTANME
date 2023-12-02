#include <pic32mx.h>
#include <stdint.h>

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

uint8_t move_repeat(uint8_t time) {
  if (time == 0) return 0;
  if (time == 1) return 3;
  if ((time<=30) && (time>=15) && time%6==0) return 1;
  if ((time>30) && (time<=60) && time%3==0) return 1;
  if ((time>60) && time%2==0) return 1;
  //if (time>60) return 1;
  return 0;
}

void cursor_movement(uint8_t *cx, uint8_t *cy, const uint8_t *input){
  //switch movement
  *cx -= move_repeat(input[4]);
  *cy -= move_repeat(input[5]);
  *cy += move_repeat(input[6]);
  *cx += move_repeat(input[7]);
}

void get_input(uint8_t *input) {
  //buttons
  if (PORTD & (1 << 7)) {
    input[0] += 1;
  } else input[0] = 0;

  if (PORTD & (1 << 6)){
    input[1] += 1;
  } else input[1] = 0;

  if (PORTD & (1 << 5)){
    input[2] += 1;
  } else input[2] = 0;

  if (PORTF & (1 << 1)){
    input[3] += 1;
  } else input[3] = 0;

  //switches
  if (PORTD & (1 << 11)) {
    input[4] += 1;
  } else input[4] = 0;
  
  if (PORTD & (1 << 10)) {
    input[5] += 1;
  } else input[5] = 0;

  if (PORTD & (1 << 9)) {
    input[6] += 1;
  } else input[6] = 0;

  if (PORTD & (1 << 8)) {
    input[7] += 1;
  } else input[7] = 0;
}