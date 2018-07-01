#include "delay.h"

void delay(unsigned int time){
    unsigned int a, b;
    for (a = time; a > 0; --a)
    {
        for (b = 0xFFF; b > 0; --b)
        {
          asm(" nop");
        }
    }
}