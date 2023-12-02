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

void cursor_movement(uint8_t *cx, uint8_t *cy){
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