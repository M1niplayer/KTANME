#include <pic32mx.h>

void interrupt(void)
{
  return;
}

int main(void) {
    TRISE = 0;
    PORTE = 1;
    while(1) {
        
    }
    return 0;
}