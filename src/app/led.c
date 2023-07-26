
#include "led.h"
#include <msp430.h>


void init_led()
{
    P1DIR |= redLED; // Direct pin as output
    P9DIR |= greenLED; // Direct pin as output
    P1OUT &= ~redLED; // Turn LED Off
    P9OUT |= greenLED; // Turn LED on
}