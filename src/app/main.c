// Timer_A up mode, with interrupt, flashes LEDs
#include <msp430.h>
#include "main.h"
#include "clocks.h"
#include "led.h"

#define redLED BIT0 // Red LED at P1.0
#define greenLED BIT7 // Green LED at P9.7

void main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop the Watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Enable the GPIO pins

    init_led();

    // Configure ACLK to the 32 KHz crystal
    config_ACLK_to_32KHz();

    // Configure Channel 0 for up mode with interrupt
    TA0CCR0 |= 3276; // Fill to get 1 second @ 32kHz; to get 0.5 second delay, set to 16383; to get 0.1 second delay, set to 3276
    TA0CCTL0 |= CCIE; // Enable Channel 0 CCIE bit
    TA0CCTL0 &= ~CCIFG;  // Clear Channel 0 CCIFG bit

    // Timer_A configuration (fill the line below)
    // Use ACLK, divide by 1, up mode, TAR cleared (leaves TAIE=0)
    TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    // Enable the global interrupt bit (call an intrinsic function)
    _enable_interrupts();

    // Infinite loop... the code waits here between interrupts
    for(;;) {}
}

#pragma vector = TIMER0_A0_VECTOR // Link the ISR to the vector
__interrupt void T0A0_ISR() {
    // Toggle both LEDs
    P1OUT ^= redLED;
    P9OUT ^= greenLED;
}